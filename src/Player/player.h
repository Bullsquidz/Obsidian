#ifndef PLAYER_H
#define PLAYER_H

#include <SDL3/SDL.h>
#include "obsidian.h"
#include "textureTown.h"
#include "map.h"

class Player{

		public:
				float speed = .10;
				float r = -OBSIDIANPI/2;
				int renderDistance = 8;
				int FOV = 120;

				vec2 inpt;

				fvec2 vel;

				vec2 tPos;
				fvec2 pos;

				fvec2 fdir;
				fvec2 sdir;
				
				void input(SDL_Event& e);
				void draw(SDL_Renderer* renderer);
				void move();
				void vision(SDL_Renderer* renderer);
				Player();
				~Player();

		private:
				Texture* texture;
};

#endif
