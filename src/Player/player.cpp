#include "player.h"
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>
#include <cmath>

void Player::input(SDL_Event& e){
		if (e.type == SDL_EVENT_KEY_DOWN && e.key.repeat == 0){
				switch(e.key.key){
						case SDLK_W: vel.y -= speed; break;
						case SDLK_S: vel.y += speed; break;
						case SDLK_A: vel.x -= speed; break;
						case SDLK_D: vel.x += speed; break;
				}
		}else if (e.type == SDL_EVENT_KEY_UP && e.key.repeat == 0){
				switch(e.key.key){	
						case SDLK_W: vel.y += speed; break;
						case SDLK_S: vel.y -= speed; break;
						case SDLK_A: vel.x += speed; break;
						case SDLK_D: vel.x -= speed; break;
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

		dir.x = std::cos(r);
		dir.y = std::sin(r);

		SDL_Log("%f, %f",dir.x, dir.y);
}

void Player::move(){
		pos.x += dir.x * (deltaTime/2) * speed;
		pos.y += dir.y * (deltaTime/2) * speed;
}

void Player::draw(SDL_Renderer* renderer){
		SDL_FRect rect{
				static_cast<float>(pos.x),
				static_cast<float>(pos.y),
				static_cast<float>(15),
				static_cast<float>(15)
		};

		SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderFillRect(renderer, &rect);

		SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
		SDL_RenderLine(renderer, pos.x + 7, pos.y + 7, pos.x + 7 + (dir.x * 20), pos.y + 7 + (dir.y * 20));
}

Player::Player(){pos.x = 15; pos.y = 15;}
Player::~Player(){}
