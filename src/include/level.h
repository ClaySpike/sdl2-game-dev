#ifndef LEVEL_H
#define LEVEL_H

#include <SDL2/SDL.h>
#include "tile.h"

struct level {
    int width;
    int height;
    struct tile *data;
};

struct level *retrieveLevelFromFile(char *);
void saveLevelToFile(struct level *, char *);
struct level *createLevel(int, int);
void freeLevel(struct level *);
void renderLevel(SDL_Renderer *, SDL_Texture *, struct level *, SDL_Point, float);

#endif