#ifndef CELL_H
#define CELL_H

#include "texture.h"
#include "obsidian.h"
class Cell{
		public:
				std::string getTName();
				void setTexture(Texture* texture);
				void draw(SDL_Renderer* renderer, float x, float y);
				Cell(std::string tName = "Unassigned");
				~Cell();

		private:
				std::string tName;
				Texture* texture;
				SDL_FRect mesh;
};

#endif
