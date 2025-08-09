#ifndef MENU_UI
#define MENU_UI

#include <ncursesw/ncurses.h>
#include <string>
#include <vector>

struct MenuOption {
    std::string text;
    int id;
};

int centerText(int max_cols, const std::string& text);
void drawTitle(WINDOW* win, int max_cols);
void drawTextBox(WINDOW* win, int max_cols, int start_y);
void drawMenuOptions(WINDOW* win, const std::vector<MenuOption>& options, int selected, int max_cols, int start_y);
int mainMenu();

#endif