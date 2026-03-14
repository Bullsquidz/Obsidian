#ifndef PLAYER_H
#define PLAYER_H

#include <SDL3/SDL.h>
#include <SDL3/SDL_render.h>
#include "obsidian.h"
#include "textureTown.h"
#include "map.h"

class Player{

		public:
				float speed = .05;
				float r = -OPI/2 + OEPSI;
				int renderDistance = 80;
				int FOV = 120;

				int numOfColumns = 266;

				vec2 inpt;

				fvec2 vel;

				vec2 tPos;
				fvec2 pos;

				fvec2 fdir;
				fvec2 sdir;
				
				void input(SDL_Event& e);
				void draw(SDL_Renderer* renderer);
				void move();
				void outOfBoundsVision(fvec2& cellPoint);
				bool checkVision(fvec2& cellPoint, SDL_Renderer* renderer);
				void vision(SDL_Renderer* renderer);

				void renderColumn(SDL_Renderer* renderer, fvec2 rayPoint, float distance, int iteration, float shade);
				Player();
				~Player();

		private:
Texture* texture;
};

#endif
