#include "ui/gameUI.hpp"
#include "core/playerState.hpp"

gameUI::gameUI(int h, int w, int y, int x, playerState& p)
    : height(h), width(w), starty(y), startx(x), player(p)
{
    win = newwin(height, width, starty, startx);

    start_color();
    use_default_colors();
    init_pair(10, COLOR_WHITE, -1);
    init_pair(11, COLOR_RED, -1);
    init_pair(12, COLOR_GREEN, -1);
    init_pair(13, COLOR_YELLOW, -1);
    init_pair(14, COLOR_CYAN, -1);
}

gameUI::~gameUI() {
    if (win) {
        delwin(win);
        win = nullptr;
    }
}

void gameUI::draw() {
    werase(win);
    box(win, 0, 0);
    wattron(win, A_BOLD | COLOR_PAIR(10));
    mvwprintw(win, 1, 1, "--------------- STATS ----------------");
    wattroff(win, A_BOLD | COLOR_PAIR(10));
    drawStats();
    wattron(win, A_BOLD | COLOR_PAIR(10));
    mvwprintw(win, 11, 1, "------------- INVENTORY --------------");
    wattroff(win, A_BOLD | COLOR_PAIR(10));
    drawInvPrev();
    wrefresh(win);
}

void gameUI::drawBar(int y, int x, int value, int color_pair) {
    int filled = value / 5;
    int empty = 20 - filled;

    wprintw(win, "[");
    wattron(win, COLOR_PAIR(color_pair));
    for (int i = 0; i < filled; i++) {
        wprintw(win, "█");
    }
    for (int i = 0; i < empty; i++) {
        wprintw(win, " ");
    }
    wattroff(win, COLOR_PAIR(color_pair));
    wprintw(win, "]");
}

void gameUI::drawStats() {
    int yPos = 3;

    wattron(win, A_BOLD | COLOR_PAIR(10));
    mvwprintw(win, yPos++, 2, "Health   ");
    wattroff(win, A_BOLD | COLOR_PAIR(10));
    drawBar(yPos++, 2, player.health, 11);

    wattron(win, A_BOLD | COLOR_PAIR(10));
    mvwprintw(win, yPos++, 2, "Stamina  ");
    wattroff(win, A_BOLD | COLOR_PAIR(10));
    drawBar(yPos++, 2, player.stamina, 12);

    wattron(win, A_BOLD | COLOR_PAIR(10));
    mvwprintw(win, yPos++, 2, "Hunger   ");
    wattroff(win, A_BOLD | COLOR_PAIR(10));
    drawBar(yPos++, 2, player.hunger, 13);

    wattron(win, A_BOLD | COLOR_PAIR(10));
    mvwprintw(win, yPos++, 2, "Thirst   ");
    wattroff(win, A_BOLD | COLOR_PAIR(10));
    drawBar(yPos++, 2, player.thirst, 14);
}

void gameUI::drawInvPrev() {
    wattron(win, A_BOLD | COLOR_PAIR(10));
    mvwprintw(win, 13, 1, "        Press ");

    wattron(win, A_BOLD | COLOR_PAIR(13));
    wprintw(win, "[J]");

    wattron(win, A_BOLD | COLOR_PAIR(10));
    wprintw(win, " for full view");

    wattroff(win, A_BOLD | COLOR_PAIR(10) | COLOR_PAIR(13));
}