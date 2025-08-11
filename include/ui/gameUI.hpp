#ifndef GAME_UI
#define GAME_UI

#include <ncurses.h>

class gameUI {
public:
    gameUI(int height, int width, int starty, int startx);
    ~gameUI();

    void draw();

    void setHealth(int val) { health = val; }
    void setStamina(int val) { stamina = val; }
    void setHunger(int val) { hunger = val; }
    void setThirst(int val) { thirst = val; }

    int health = 100;
    int stamina = 100;
    int hunger = 100;
    int thirst = 100;

private:
    WINDOW* win;
    int height, width, starty, startx;

    void drawBar(int y, int x, int value, int color_pair);
    void drawStats();
};

#endif
