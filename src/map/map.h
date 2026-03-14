#ifndef MAP_H
#define MAP_H

#include<SDL3/SDL.h>
#include "cellCity.h"

const int MAPSIZE = 24;
const int MAPOFFSET = hCSize;
extern bool showMap;

extern int demoMap[MAPSIZE][MAPSIZE];

void drawMap(SDL_Renderer* renderer);
#endif
