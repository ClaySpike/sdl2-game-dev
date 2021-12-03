#include "level.h"
#include "tile.h"
#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>

int NiceTiles[] = {-18, -21, -19, -20, -8, -11, -9, -10, 12, 9, 11, 10, 2, -1, 1, 0};

struct level *retrieveLevelFromFile(char *path) {
    FILE *file = fopen(path, "r");
    if (file == NULL) {
        return NULL;
    }

    struct level *lvl = malloc(sizeof(struct level));
    if (lvl == NULL) {
        fclose(file);
        return NULL;
    }

    fread(&(lvl->width), sizeof(int), 1, file);
    fread(&(lvl->height), sizeof(int), 1, file);
    lvl->data = malloc(sizeof(struct tile) * lvl->width * lvl->height);
    if (lvl->data == NULL) {
        free(lvl);
        fclose(file);
        return NULL;
    }

    fread(lvl->data, sizeof(struct tile) * lvl->width * lvl->height, 1, file);
    
    return lvl;
}

void saveLevelToFile(struct level *lvl, char *path) {
    if (lvl == NULL) {
        return;
    }
    
    FILE *file = fopen(path, "w");
    if (file == NULL) {
        return;
    }

    fwrite(&lvl->width, sizeof(int), 1, file);
    fwrite(&lvl->height, sizeof(int), 1, file);
    fwrite(lvl->data, sizeof(struct tile) * lvl->width * lvl->height, 1, file);
    fclose(file);
}

struct level *createLevel(int width, int height) {
    if (width < 0 || height < 0) {
        return NULL;
    }

    struct level *lvl = malloc(sizeof(struct level));
    if (lvl == NULL) {
        return NULL;
    }

    lvl->width = width;
    lvl->height = height;
    lvl->data = malloc(sizeof(struct tile) * width * height);
    if (lvl->data == NULL) {
        free(lvl);
        return NULL;
    }

    return lvl;
}

void freeLevel(struct level *lvl) {
    if (lvl == NULL) {
        return;
    }

    free(lvl->data);
    lvl->data = 0;
    free(lvl);
    lvl = 0;
}

void renderLevel(SDL_Renderer *renderer, SDL_Texture *spriteSheet, struct level *lvl, SDL_Point pos, float zoom) {
    for (int i = 0; i < lvl->height; i++) {
        for (int j = 0; j < lvl->width; j++) {
            int check = lvl->data[i * lvl->height + j].floor;
            if (check == LIGHT_SOIL) {
                SDL_Rect src_loc = convertToSpriteSheet(90);
                SDL_Rect dest_loc = {pos.x + j*src_loc.w*zoom, pos.y + i*src_loc.h*zoom, src_loc.w*zoom, src_loc.h*zoom};
                SDL_RenderCopy(renderer, spriteSheet, &src_loc, &dest_loc);
            }
            else if (check == DARK_SOIL) {
                int location = 0;
                if (i - 1 >= 0 && lvl->data[(i-1) * lvl->height + j].floor == DARK_SOIL) {
                    location += 8;
                }
                if (i + 1 < lvl->height && lvl->data[(i+1) * lvl->height + j].floor == DARK_SOIL) {
                    location += 4;
                }
                if (j - 1 >= 0 && lvl->data[i * lvl->height + j-1].floor == DARK_SOIL) {
                    location += 2;
                }
                if (j + 1 < lvl->width && lvl->data[i * lvl->height + j+1].floor == DARK_SOIL) {
                    location += 1;
                }
                SDL_Rect src_loc = convertToSpriteSheet(71 + NiceTiles[location]);

                SDL_Rect dest_loc = {pos.x + j*src_loc.w*zoom, pos.y + i*src_loc.h*zoom, src_loc.w*zoom, src_loc.h*zoom};
                SDL_RenderCopy(renderer, spriteSheet, &src_loc, &dest_loc);
            }
            else if (check == ROCKY_SOIL) {
                int location = 0;
                if (i - 1 >= 0 && lvl->data[(i-1) * lvl->height + j].floor == ROCKY_SOIL) {
                    location += 8;
                }
                if (i + 1 < lvl->height && lvl->data[(i+1) * lvl->height + j].floor == ROCKY_SOIL) {
                    location += 4;
                }
                if (j - 1 >= 0 && lvl->data[i * lvl->height + j-1].floor == ROCKY_SOIL) {
                    location += 2;
                }
                if (j + 1 < lvl->width && lvl->data[i * lvl->height + j+1].floor == ROCKY_SOIL) {
                    location += 1;
                }
                SDL_Rect src_loc = convertToSpriteSheet(121 + NiceTiles[location]);
                SDL_Rect dest_loc = {pos.x + j*src_loc.w*zoom, pos.y + i*src_loc.h*zoom, src_loc.w*zoom, src_loc.h*zoom};
                SDL_RenderCopy(renderer, spriteSheet, &src_loc, &dest_loc);
            }

            check = lvl->data[i * lvl->height + j].placed;
            if (check == WALL) {
                SDL_Rect src_loc = convertToSpriteSheet(0);
                SDL_Rect dest_loc = {pos.x + j*src_loc.w*zoom, pos.y + i*src_loc.h*zoom, src_loc.w*zoom, src_loc.h*zoom};
                SDL_RenderCopy(renderer, spriteSheet, &src_loc, &dest_loc);
            }
            else if (check == RAIL) {
                SDL_Rect src_loc = convertToSpriteSheet(1);
                SDL_Rect dest_loc = {pos.x + j*src_loc.w*zoom, pos.y + i*src_loc.h*zoom, src_loc.w*zoom, src_loc.h*zoom};
                SDL_RenderCopy(renderer, spriteSheet, &src_loc, &dest_loc);
            }
            else if (check == LEVER) {
                SDL_Rect src_loc = convertToSpriteSheet(41);
                SDL_Rect dest_loc = {pos.x + j*src_loc.w*zoom, pos.y + i*src_loc.h*zoom, src_loc.w*zoom, src_loc.h*zoom};
                SDL_RenderCopy(renderer, spriteSheet, &src_loc, &dest_loc);
            }
            else if (check == SIGN) {
                SDL_Rect src_loc = convertToSpriteSheet(43);
                SDL_Rect dest_loc = {pos.x + j*src_loc.w*zoom, pos.y + i*src_loc.h*zoom, src_loc.w*zoom, src_loc.h*zoom};
                SDL_RenderCopy(renderer, spriteSheet, &src_loc, &dest_loc);
            }
            else if (check == ROCK) {
                SDL_Rect src_loc = convertToSpriteSheet(46);
                SDL_Rect dest_loc = {pos.x + j*src_loc.w*zoom, pos.y + i*src_loc.h*zoom, src_loc.w*zoom, src_loc.h*zoom};
                SDL_RenderCopy(renderer, spriteSheet, &src_loc, &dest_loc);
            }
            else if (check == LAMP) {
                SDL_Rect src_loc = convertToSpriteSheet(95);
                SDL_Rect dest_loc = {pos.x + j*src_loc.w*zoom, pos.y + i*src_loc.h*zoom, src_loc.w*zoom, src_loc.h*zoom};
                SDL_RenderCopy(renderer, spriteSheet, &src_loc, &dest_loc);
            }
        }
    }
}