#ifndef GAME_UI
#define GAME_UI

#include <ncurses.h>
#include "core/playerState.hpp"

class gameUI {
public:
    gameUI(int height, int width, int starty, int startx, playerState& p);
    ~gameUI();

    void draw();

private:
    WINDOW* win;
    int height, width, starty, startx;

    void drawBar(int y, int x, int value, int color_pair);
    void drawStats();
    void drawInvPrev();

    playerState& player;
};

#endif
