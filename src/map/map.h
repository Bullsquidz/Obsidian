#ifndef MAP_H
#define MAP_H

#include<SDL3/SDL.h>
#include "cellCity.h"

const int MAPSIZE = 42;
const int MAPOFFSET = hCSize;

extern int demoMap[MAPSIZE][MAPSIZE];

void drawMap(SDL_Renderer* renderer);
#endif
