#include "player.h"
#include "obsidian.h"
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>
#include <cmath>

void Player::input(SDL_Event& e){
		if (e.type == SDL_EVENT_KEY_DOWN && e.key.repeat == 0){
				switch(e.key.key){
						case SDLK_W: inpt.y += 1; break;
						case SDLK_S: inpt.y -= 1; break;
						case SDLK_A: inpt.x -= 1; break;
						case SDLK_D: inpt.x += 1; break;
				}
		}else if (e.type == SDL_EVENT_KEY_UP && e.key.repeat == 0){
				switch(e.key.key){	
						case SDLK_W: inpt.y -= 1; break;
						case SDLK_S: inpt.y += 1; break;
						case SDLK_A: inpt.x += 1; break;
						case SDLK_D: inpt.x -= 1; break;
				}
		}

		//ORIENTATION
		switch(e.key.key){
				case SDLK_E: r += OBSIDIANPI/15; break;
				case SDLK_Q: r -= OBSIDIANPI/15; break;
		}
		if ( r >= (2 * OBSIDIANPI + OBSIDIANPI/2) )
				r =  (-2 * OBSIDIANPI + OBSIDIANPI/2);
		else if ( r <= (-2 * OBSIDIANPI + OBSIDIANPI/2) )
				r = (2 * OBSIDIANPI + OBSIDIANPI/2);



		fdir.x = std::cos(r);
		fdir.y = std::sin(r);
		sdir.x = -std::sin(r);
		sdir.y = std::cos(r);

		//SDL_Log("Input  <%d, %d>\n", pos.x, pos.y);
		//SDL_Log("Position  <%d, %d>\n", pos.x, pos.y);
		//SDL_Log("Direction <%f, %f>\n", fdir.x, fdir.y);
		//SDL_Log("\n\n");
}

void Player::move(){
		float normalize = 1;
		if (inpt.x != 0 && inpt.y != 0)
				normalize = std::sqrt( std::pow(inpt.x,2) + std::pow(inpt.y,2) );

		pos.x += (sdir.x * (inpt.x/normalize)  + fdir.x * (inpt.y/normalize)) * (deltaTime/2) * speed;
		pos.y += (fdir.y * (inpt.y/normalize)  + sdir.y * (inpt.x/normalize)) * (deltaTime/2) * speed;
}

void Player::draw(SDL_Renderer* renderer){
		SDL_FRect rect{
				static_cast<float>(pos.x),
				static_cast<float>(pos.y),
				static_cast<float>(eSize),
				static_cast<float>(eSize)
		};

		SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderFillRect(renderer, &rect);

		SDL_SetRenderDrawColor(renderer, 0x00, 0xFF, 0x00, 0xFF);
		SDL_RenderLine(renderer, 
						pos.x + hESize, 
						pos.y + hESize, 
						pos.x + hESize + (fdir.x * 20), 
						pos.y + hESize + (fdir.y * 20));


		SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
		SDL_RenderLine(renderer, 
						pos.x + hESize, 
						pos.y + hESize, 
						pos.x + hESize + (sdir.x * 10), 
						pos.y + hESize + (sdir.y * 10));


}

Player::Player(){pos.x = 100; pos.y = 100;}
Player::~Player(){}
