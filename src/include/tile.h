#ifndef TILE_H
#define TILE_H
#include <SDL2/SDL.h>

#define LIGHT_SOIL 0
#define DARK_SOIL 1
#define ROCKY_SOIL 2

#define EMPTY 0
#define WALL 1
#define RAIL 2
#define LEVER 3
#define SIGN 4
#define ROCK 5
#define LAMP 6

struct tile {
    unsigned int floor;
    unsigned char solid;
    int placed;
    void *state;
};

SDL_Rect convertToSpriteSheet(int);
void freeTile(struct tile *);

#endif