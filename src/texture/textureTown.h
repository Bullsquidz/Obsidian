#ifndef TEXTURETOWN_H
#define TEXTURETOWN_H

#include <map>
#include <string>
#include "texture.h"

extern std::map<std::string, Texture> textures;

bool initTexture(SDL_Renderer* renderer);

void desTexture();

#endif
