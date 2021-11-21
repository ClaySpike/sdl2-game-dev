#include "level.h"
#include "tile.h"
#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>

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