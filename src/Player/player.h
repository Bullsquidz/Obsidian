#ifndef PLAYER_H
#define PLAYER_H

#include <SDL3/SDL.h>
#include "obsidian.h"

class Player{

		public:
				float speed = .5;
				float r = -OBSIDIANPI/2;

				vec2 inpt;

				fvec2 vel;
				fvec2 pos;

				fvec2 fdir;
				fvec2 sdir;
				
				void input(SDL_Event& e);
				void draw(SDL_Renderer* renderer);
				void move();
				Player();
				~Player();

};

#endif
