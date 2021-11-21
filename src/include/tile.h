#ifndef TILE_H
#define TILE_H
#include <SDL2/SDL.h>

struct tile {
    unsigned int floor;
    unsigned char solid;
    int placed;
};

SDL_Rect convertToSpriteSheet(int);

#endif