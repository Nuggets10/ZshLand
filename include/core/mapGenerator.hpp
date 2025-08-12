#ifndef MAP_GENERATOR
#define MAP_GENERATOR

#include <ncursesw/ncurses.h>
#include <string>
#include <vector>
#include "core/playerState.hpp" // serve per conoscere playerState

class mapGenerator {
public:
    int generateMap();

private:
    playerState player; // membro della classe
};

#endif
