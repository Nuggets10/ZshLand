#include <ncursesw/ncurses.h>
#include <vector>
#include <locale.h>
#include <ctime>
#include "core/perlinNoise.hpp"

const int width = 3000;
const int height = 3000;
const double scale = 0.025;

int generateMap() {
    setlocale(LC_ALL, "");
    initscr();
    keypad(stdscr, TRUE);
    noecho();
    curs_set(0);
    start_color();
    use_default_colors();

    init_pair(1, COLOR_CYAN, -1);    // Water
    init_pair(2, COLOR_YELLOW, -1);  // Beach
    init_pair(3, COLOR_GREEN, -1);   // Plains
    init_pair(4, COLOR_GREEN, -1);   // Hills
    init_pair(5, COLOR_BLACK, -1);   // Mountains
    init_pair(6, COLOR_WHITE, -1);   // Snow
    init_pair(7, COLOR_YELLOW, -1);  // Trees

    std::uint32_t seed = static_cast<std::uint32_t>(time(nullptr));
    siv::PerlinNoise perlin(seed);

    std::vector<std::vector<wchar_t>> map(height, std::vector<wchar_t>(width));

    for (int y = 0; y < height; ++y)
        for (int x = 0; x < width; ++x) {
            double noise = perlin.noise2D_01(x * scale, y * scale);
            if (noise < 0.3)
                map[y][x] = L'█'; // Water
            else if (noise < 0.35)
                map[y][x] = L'▒'; // Beach
            else if (noise < 0.55)
                map[y][x] = (rand() % 100 < 90) ? L'#' : rand() % 2 ? L'↑' : L'Y'; // Plains
            else if (noise < 0.7)
                map[y][x] = (rand() % 100 < 96) ?
                    ((rand() % 2) ? L'n' : L'm')
                    : rand() % 2 ? L'↑' : L'Y';
            else if (noise < 0.8)
                map[y][x] = L'▓'; // Mountains
            else
                map[y][x] = L'▇'; // Snow
        }

    int screenW, screenH;
    getmaxyx(stdscr, screenH, screenW);
    int camX = screenW / 2;
    int camY = screenH / 2;

    bool running = true;
    while (running) {
        clear();

        for (int y = 0; y < screenH; ++y) {
            int mapY = camY + y;
            if (mapY >= height) break;

            move(y, 0);
            for (int x = 0; x < screenW; ++x) {
                int mapX = camX + x;
                if (mapX >= width) break;

                wchar_t tile = map[mapY][mapX];

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
                else if (tile == L'n' || tile == L'm' || tile == L'↑' || tile == L'¶') {
                    if (tile == L'↑' || tile == L'Y')
                        attron(COLOR_PAIR(7));
                    else
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

        int ch = getch();

        int playerX = camX + screenW / 2;
        int playerY = camY + screenH / 2;

        switch (ch) {
            case KEY_LEFT:
                if (playerX > 0 && playerY >= 0 && playerY < height) {
                    wchar_t nextTile = map[playerY][playerX - 1];
                    if (nextTile != L'Y' && nextTile != L'↑' && nextTile != L'█' &&
                        nextTile != L'▓' && nextTile != L'▇') {
                        camX--;
                    }
                }
                break;
            case KEY_RIGHT:
                if (playerX < width - 1 && playerY >= 0 && playerY < height) {
                    wchar_t nextTile = map[playerY][playerX + 1];
                    if (nextTile != L'Y' && nextTile != L'↑' && nextTile != L'█' &&
                        nextTile != L'▓' && nextTile != L'▇') {
                        camX++;
                    }
                }
                break;
            case KEY_UP:
                if (playerY > 0 && playerX >= 0 && playerX < width) {
                    wchar_t nextTile = map[playerY - 1][playerX];
                    if (nextTile != L'Y' && nextTile != L'↑' && nextTile != L'█' &&
                        nextTile != L'▓' && nextTile != L'▇') {
                        camY--;
                    }
                }
                break;
            case KEY_DOWN:
                if (playerY < height - 1 && playerX >= 0 && playerX < width) {
                    wchar_t nextTile = map[playerY + 1][playerX];
                    if (nextTile != L'Y' && nextTile != L'↑' && nextTile != L'█' &&
                        nextTile != L'▓' && nextTile != L'▇') {
                        camY++;
                    }
                }
                break;
            case 'q':
            case 'Q':
                running = false;
                break;
        }

        camX = std::max(0, std::min(camX, width - screenW));
        camY = std::max(0, std::min(camY, height - screenH));

    }
    endwin();
    return 0;
}
