#include "tile.h"
#include <SDL2/SDL.h>
#include <stdlib.h>

/* This function converts a single number
 * into a location on the Sprite Sheet tileset.png
 */
SDL_Rect convertToSpriteSheet(int num) {
    if (num < 0) {
        return (SDL_Rect){0, 0, 0, 0};
    }

    return (SDL_Rect){(num % 10) * 16, (num / 10) * 16, 16, 16};
}

void freeTile(struct tile *t) {
    free(t);
    t = 0;
}