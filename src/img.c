#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "image.h"

SDL_Texture *importToTexture(SDL_Renderer *renderer, char *path) {
    SDL_Surface *image = IMG_Load(path);
    if (image == NULL) {
        return NULL;
    }

    SDL_Texture *tex = SDL_CreateTextureFromSurface(renderer, image);
    SDL_FreeSurface(image);
    image = NULL;
    return tex;
}