#include <ncursesw/ncurses.h>
#include <vector>
#include <locale.h>
#include <ctime>
#include <mutex>
#include "core/perlinNoise.hpp"
#include "ui/gameUI.hpp"
#include "core/playerState.hpp"
#include <chrono>
#include <thread>
#include <atomic>

const int width = 3000;
const int height = 3000;
const double scale = 0.025;

class mapGenerator {
public:
    int generateMap();
};

int mapGenerator::generateMap() {
    setlocale(LC_ALL, "");
    initscr();
    keypad(stdscr, TRUE);
    noecho();
    curs_set(0);
    start_color();
    use_default_colors();
    nodelay(stdscr, TRUE);

    init_pair(1, COLOR_CYAN, -1);    // Water
    init_pair(2, COLOR_YELLOW, -1);  // Beach
    init_pair(3, COLOR_GREEN, -1);   // Plains
    init_pair(4, COLOR_GREEN, -1);   // Hills
    init_pair(5, COLOR_BLACK, -1);   // Mountains
    init_pair(6, COLOR_WHITE, -1);   // Snow
    init_pair(7, COLOR_YELLOW, -1);  // Trees

    std::uint32_t seed = static_cast<std::uint32_t>(time(nullptr));
    siv::PerlinNoise perlin(seed);

    // --- Cache creation
    std::vector<std::vector<wchar_t>> map(height, std::vector<wchar_t>(width, L'\0'));
    std::mutex mapMutex;
    std::atomic<bool> stopGen{false};

    // --- RNG for each cell
    auto splitmix64 = [](uint64_t x) {
        x += 0x9e3779b97f4a7c15ULL;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9ULL;
        x = (x ^ (x >> 27)) * 0x94d049bb133111ebULL;
        return x ^ (x >> 31);
    };
    auto cellRand = [&](int x, int y, uint64_t salt = 0) -> uint32_t {
        uint64_t k = (uint64_t(seed) << 32) ^ (uint64_t(uint32_t(x)) << 1) ^ (uint64_t(uint32_t(y)) << 33) ^ salt;
        return uint32_t(splitmix64(k));
    };
    auto cellRand01 = [&](int x, int y, uint64_t salt = 0) -> double {
        return (cellRand(x, y, salt) / double(UINT32_MAX));
    };

    // --- Generation of each tile based on RNG
    auto makeTile = [&](int x, int y) -> wchar_t {
        double noise = perlin.noise2D_01(x * scale, y * scale);
        if (noise < 0.3)  return L'█';
        if (noise < 0.35) return L'▒';
        if (noise < 0.55) {
            double r = cellRand01(x, y, 1);
            if (r < 0.90) return L'#';
            return (cellRand(x, y, 2) & 1) ? L'↑' : L'Y';
        }
        if (noise < 0.7) {
            double r = cellRand01(x, y, 3);
            if (r < 0.96)
                return (cellRand(x, y, 4) & 1) ? L'n' : L'm';
            return (cellRand(x, y, 5) & 1) ? L'↑' : L'Y';
        }
        if (noise < 0.8) return L'▓';
        return L'▇';
    };

    // --- If not generated put it in cache
    auto getTile = [&](int x, int y) -> wchar_t {
        if (x < 0 || y < 0 || x >= width || y >= height) return L' ';
        {
            std::lock_guard<std::mutex> lk(mapMutex);
            if (map[y][x] != L'\0') return map[y][x];
        }
        wchar_t t = makeTile(x, y);
        {
            std::lock_guard<std::mutex> lk(mapMutex);
            if (map[y][x] == L'\0') map[y][x] = t;
            return map[y][x];
        }
    };

    // --- Chunk generation
    struct Chunk { int x0, y0, w, h; };
    auto genChunkIntoMap = [&](const Chunk& c) {
        std::vector<wchar_t> buf(c.w * c.h);
        for (int dy = 0; dy < c.h; ++dy) {
            int y = c.y0 + dy;
            if (y < 0 || y >= height) continue;
            for (int dx = 0; dx < c.w; ++dx) {
                int x = c.x0 + dx;
                if (x < 0 || x >= width) continue;
                buf[dy * c.w + dx] = makeTile(x, y);
            }
        }
        std::lock_guard<std::mutex> lk(mapMutex);
        for (int dy = 0; dy < c.h; ++dy) {
            int y = c.y0 + dy; if (y < 0 || y >= height) continue;
            for (int dx = 0; dx < c.w; ++dx) {
                int x = c.x0 + dx; if (x < 0 || x >= width) continue;
                if (map[y][x] == L'\0') map[y][x] = buf[dy * c.w + dx];
            }
        }
    };

    // --- Load order of chunks
    auto spiralChunks = [&](int chunkSize) {
        std::vector<Chunk> out;
        int cx = width / 2, cy = height / 2;
        int r = 0;
        while (true) {
            bool added = false;
            for (int by = cy - r * chunkSize; by <= cy + r * chunkSize; by += chunkSize) {
                for (int bx = cx - r * chunkSize; bx <= cx + r * chunkSize; bx += chunkSize) {
                    if (by != cy - r * chunkSize && by != cy + r * chunkSize &&
                        bx != cx - r * chunkSize && bx != cx + r * chunkSize) continue;
                    Chunk c{bx, by, chunkSize, chunkSize};
                    if (c.x0 >= width || c.y0 >= height || c.x0 + c.w <= 0 || c.y0 + c.h <= 0) continue;
                    out.push_back(c);
                    added = true;
                }
            }
            if (!added) break;
            if ((cx - (r+1)*chunkSize <= 0 && cy - (r+1)*chunkSize <= 0 &&
                 cx + (r+1)*chunkSize >= width && cy + (r+1)*chunkSize >= height)) break;
            ++r;
        }
        return out;
    };

    // --- Load chunk around the player
    int screenW, screenH;
    getmaxyx(stdscr, screenH, screenW);
    int camX = (width  - screenW) / 2;
    int camY = (height - screenH) / 2;

    auto preloadView = [&](){
        int pad = 2;
        Chunk c{
            std::max(0, camX - pad),
            std::max(0, camY - pad),
            std::min(width  - std::max(0, camX - pad), screenW + 2 * pad),
            std::min(height - std::max(0, camY - pad), screenH + 2 * pad)
        };
        genChunkIntoMap(c);
    };
    preloadView();

    // --- Background terrain generation using threads
    const int chunkSize = 200;
    std::thread bg([&]{
        auto order = spiralChunks(chunkSize);
        for (const auto& c : order) {
            if (stopGen.load()) break;
            genChunkIntoMap(c);
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }
    });
    bg.detach();

    // --- UI
    int h, w;
    getmaxyx(stdscr, h, w);
    playerState player;
    gameUI menu(h, 40, 0, w - 40, player);

    bool running = true;
    auto lastStaminaUpdate = std::chrono::steady_clock::now();
    auto lastHungerUpdate  = std::chrono::steady_clock::now();
    auto lastThirstUpdate  = std::chrono::steady_clock::now();

    while (running) {
        clear();

        for (int y = 0; y < screenH; ++y) {
            int mapY = camY + y;
            if (mapY >= height) break;
            move(y, 0);
            for (int x = 0; x < screenW; ++x) {
                int mapX = camX + x;
                if (mapX >= width) break;

                wchar_t tile = getTile(mapX, mapY);

                if (y == screenH / 2 && x == screenW / 2) {
                    attron(A_BOLD | COLOR_PAIR(6));
                    addch('P');
                    attroff(A_BOLD | COLOR_PAIR(6));
                    continue;
                }

                if (tile == L'█')
                    attron(COLOR_PAIR(1));
                else if (tile == L'▒')
                    attron(A_BOLD | COLOR_PAIR(2));
                else if (tile == L'#' || tile == L'↑' || tile == L'Y') {
                    if (tile == L'#')
                        attron(A_BOLD | COLOR_PAIR(3));
                    else
                        attron(COLOR_PAIR(7));
                }
                else if (tile == L'n' || tile == L'm' || tile == L'¶') {
                    attron(COLOR_PAIR(4));
                }
                else if (tile == L'▓')
                    attron(A_BOLD | COLOR_PAIR(5));
                else
                    attron(COLOR_PAIR(6));

                addnwstr(&tile, 1);

                attroff(COLOR_PAIR(1));
                attroff(A_BOLD | COLOR_PAIR(2));
                attroff(A_BOLD | COLOR_PAIR(3));
                attroff(COLOR_PAIR(4));
                attroff(A_BOLD | COLOR_PAIR(5));
                attroff(COLOR_PAIR(6));
                attroff(COLOR_PAIR(7));
            }
        }

        refresh();
        menu.draw();

        int ch = getch();
        int playerX = camX + screenW / 2;
        int playerY = camY + screenH / 2;

        auto passable = [&](wchar_t t){
            return !(t == L'Y' || t == L'↑' || t == L'█' || t == L'▓' || t == L'▇');
        };

        switch (ch) {
            case KEY_LEFT:
                if (playerX > 0 && player.stamina > 1) {
                    wchar_t nextTile = getTile(playerX - 1, playerY);
                    if (passable(nextTile)) { camX--; player.decreaseStamina(5); }
                }
                break;
            case KEY_RIGHT:
                if (playerX < width - 1 && player.stamina > 1) {
                    wchar_t nextTile = getTile(playerX + 1, playerY);
                    if (passable(nextTile)) { camX++; player.decreaseStamina(5); }
                }
                break;
            case KEY_UP:
                if (playerY > 0 && player.stamina > 1) {
                    wchar_t nextTile = getTile(playerX, playerY - 1);
                    if (passable(nextTile)) { camY--; player.decreaseStamina(5); }
                }
                break;
            case KEY_DOWN:
                if (playerY < height - 1 && player.stamina > 1) {
                    wchar_t nextTile = getTile(playerX, playerY + 1);
                    if (passable(nextTile)) { camY++; player.decreaseStamina(5); }
                }
                break;
            case 'q':
            case 'Q':
                running = false;
                break;
        }

        // Generate margin around camera to not show popping effect
        preloadView();

        // Timers player
        auto now = std::chrono::steady_clock::now();
        if (std::chrono::duration<double>(now - lastStaminaUpdate).count() >= 0.25) {
            if (player.stamina < 100) player.increaseStamina(5);
            lastStaminaUpdate = now;
        }
        if (std::chrono::duration<double>(now - lastHungerUpdate).count() >= 10.0) {
            player.decreaseHunger(1);
            lastHungerUpdate = now;
        }
        if (std::chrono::duration<double>(now - lastThirstUpdate).count() >= 20.0) {
            player.decreaseThirst(1);
            lastThirstUpdate = now;
        }

        camX = std::max(0, std::min(camX, width - screenW));
        camY = std::max(0, std::min(camY, height - screenH));

        std::this_thread::sleep_for(std::chrono::milliseconds(16));
    }

    stopGen = true;
    endwin();
    return 0;
}

