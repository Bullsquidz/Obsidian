#ifndef CELLCITY_H
#define CELLCITY_H

#include <map>
#include <string>
#include "cell.h"
#include "textureTown.h"

extern std::map<std::string, Cell> cells;

bool initCells();

#endif
