#include "ui/menuUI.hpp"
#include <algorithm>
#include <sstream>
#include "core/mapGenerator.hpp"

int centerText(int max_cols, const std::string& text) {
    return (max_cols - text.length()) / 2;
}

void showMessageBox(const std::string& title, const std::string& message, int max_cols, int max_rows) {
    int box_width = 85;
    int box_height = 15;
    int start_x = (max_cols - box_width) / 2;
    int start_y = (max_rows - box_height) / 2;

    WINDOW* msg_win = newwin(box_height, box_width, start_y, start_x);
    box(msg_win, 0, 0);

    wattron(msg_win, A_BOLD | COLOR_PAIR(3));
    mvwprintw(msg_win, 1, (box_width - title.size()) / 2, "%s", title.c_str());
    wattroff(msg_win, A_BOLD | COLOR_PAIR(3));

    std::istringstream stream(message);
    std::string line;
    int y = 3;
    while (std::getline(stream, line) && y < box_height - 2) {
        mvwprintw(msg_win, y++, 2, "%s", line.c_str());
    }

    wattron(msg_win, A_REVERSE);
    mvwprintw(msg_win, box_height - 2, (box_width - 6) / 2, "[ OK ]");
    wattroff(msg_win, A_REVERSE);

    wrefresh(msg_win);
    
    // Attende invio
    while (true) {
        int ch = wgetch(msg_win);
        if (ch == '\n' || ch == KEY_ENTER || ch == 10) break;
    }

    delwin(msg_win);
}


void drawTitle(WINDOW* win, int max_cols) {
    start_color();
    init_pair(1, COLOR_GREEN, COLOR_BLACK);
    wattron(win, A_BOLD | COLOR_PAIR(1));

    const std::vector<std::string> asciiArt = {
        " _____    _     _                    _      ___   ",
        "|__  /___| |__ | |    __ _ _ __   __| |   _|   |_ ",
        "  / // __| '_ \\| |   / _` | '_ \\ / _` |  |_______|",
        " / /_\\__ \\ | | | |__| (_| | | | | (_| |     | |   ",
        "/____|___/_| |_|_____\\__,_|_| |_|\\__,_|     |_|   "
    };    
    
    int start_y = 2;
    for (const auto& line : asciiArt) {
        mvwprintw(win, start_y++, centerText(max_cols, line), "%s", line.c_str());
    }

    wattroff(win, A_BOLD | COLOR_PAIR(1));
}

void drawTextBox(WINDOW* win, int max_cols, int start_y) {
    init_pair(3, COLOR_YELLOW, -1);
    init_pair(4, COLOR_BLUE, -1);

    int box_width = 120;
    int box_height = 18;
    int box_x = (max_cols - box_width) / 2;

    WINDOW* box_win = subwin(win, box_height, box_width, start_y, box_x);
    box(box_win, 0, 0);

    wattron(box_win, A_BOLD | COLOR_PAIR(3));
    mvwprintw(box_win, 2, 2, "Version 1.0.0 - STABLE");
    wattroff(box_win, A_BOLD | COLOR_PAIR(3));

    mvwprintw(box_win, 3, 2, "Check the Github repository for full changelog:");

    wattron(box_win, A_BOLD | COLOR_PAIR(4));
    mvwprintw(box_win, 4, 2, "https://github.com/Nuggets10/ZshLand");
    wattroff(box_win, A_BOLD | COLOR_PAIR(4));

    mvwprintw(box_win, 5, 2, "");

    wattron(box_win, A_BOLD | COLOR_PAIR(3));
    mvwprintw(box_win, 6, 2, "First release");
    wattroff(box_win, A_BOLD | COLOR_PAIR(3));

    mvwprintw(box_win, 7, 2, "Added main menu");
    mvwprintw(box_win, 8, 2, "Added terrain generation using a randomly generated perlin noise map.");
    mvwprintw(box_win, 9, 2, "Added colors to display different elevations of the terrain.");
    mvwprintw(box_win, 10, 2, "Added camera  and player movement with collisions using directional arrows.");
    mvwprintw(box_win, 11, 2, "");

    init_pair(5, COLOR_RED, -1);
    wattron(box_win, A_BOLD | COLOR_PAIR(5));
    mvwprintw(box_win, 12, 2, "NOTICE: The terrain generation process may take a few seconds to complete");
    wattroff(box_win, A_BOLD | COLOR_PAIR(5));

    wrefresh(box_win);
}

void drawMenuOptions(WINDOW* win, const std::vector<MenuOption>& options, int selected, int max_cols, int start_y) {
    int menu_y = start_y;
    
    for (size_t i = 0; i < options.size(); ++i) {
        if (i == static_cast<size_t>(selected)) {
            wattron(win, A_REVERSE);
        }

        if (options[i].text.find("Start") != std::string::npos) {
            wattron(win, A_BOLD | COLOR_PAIR(1));
        } else if (options[i].text.find("Quit") != std::string::npos) {
            wattron(win, A_BOLD | COLOR_PAIR(2));
        }
        
        mvwprintw(win, menu_y++, centerText(max_cols, options[i].text), "%s", options[i].text.c_str());

        wattroff(win, A_BOLD | COLOR_PAIR(1));
        wattroff(win, A_BOLD | COLOR_PAIR(2));
        
        if (i == static_cast<size_t>(selected)) {
            wattroff(win, A_REVERSE);
        }
    }
}

int mainMenu() {
    initscr();
    cbreak();
    noecho();
    start_color();
    init_pair(1, COLOR_GREEN, COLOR_BLACK);
    init_pair(2, COLOR_RED, COLOR_BLACK);
    use_default_colors();
    curs_set(0);
    keypad(stdscr, TRUE);
    
    int max_rows, max_cols;
    getmaxyx(stdscr, max_rows, max_cols);
    
    std::vector<MenuOption> options = {
        {"[ 1) Start        ]", 1},
        {"[ 2) Report a bug ]", 2},
        {"[ 3) Contribute   ]", 3},
        {"[ 4) Quit         ]", 0}
    };
    
    int selected = 0;
    int choice;
    
    while (true) {
        clear();
        drawTitle(stdscr, max_cols);
        drawTextBox(stdscr, max_cols, 8);
        drawMenuOptions(stdscr, options, selected, max_cols, 28);
        refresh();
        
        choice = getch();
        
        switch (choice) {
            case KEY_UP:
                selected = (selected - 1 + options.size()) % options.size();
                break;
            case KEY_DOWN:
                selected = (selected + 1) % options.size();
                break;
            case '\n':
                if (options[selected].id == 2) {
                    showMessageBox("Report a Bug",
                                   "Please report any bug, feedback or suggestion in the issue tab\n"
                                   "located in the project repository:\n"
                                   "https://github.com/Nuggets10/ZshLand\n"
                                   "(CTRL + LMB on the link to open it)",
                                   max_cols, max_rows);
                } else if (options[selected].id == 3) {
                    showMessageBox("Contribute",
                                   "Before you contribute code to the project please check the\n"
                                   "contribution guidelines located in the project repository:\n"
                                   "https://github.com/Nuggets10/ZshLand\n"
                                   "To contribute to the project, you can fork the repository, make your changes and\n open a pull request. The request will be revisioned and accepted if everything \n is correct.\n"
                                   "(CTRL + LMB on the link to open it)",
                                   max_cols, max_rows);
                } else if (options[selected].id == 0) {
                    endwin();
                    return 0;
                } else {
                    generateMap();
                    return options[selected].id;
                }
                break;
            
        }
    }
}