#include "tile.h"
#include <SDL2/SDL.h>

/* This function converts a single number
 * into a location on the Sprite Sheet tileset.png
 */
SDL_Rect convertToSpriteSheet(int num) {
    return (SDL_Rect){(num % 10) * 16, (num / 10) * 16, 16, 16};
}