#include "player.h"
#include "obsidian.h"
#include <SDL3/SDL_keycode.h>
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
						case SDLK_LEFTBRACKET: renderDistance--; SDL_Log("RD: %d\n", renderDistance); break;
						case SDLK_RIGHTBRACKET: renderDistance++; SDL_Log("RD: %d\n", renderDistance); break;
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
				case SDLK_E: r += OBSIDIANPI/18; break;
				case SDLK_Q: r -= OBSIDIANPI/18; break;
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
		//SDL_Log("T.Position  <%d, %d>\n", tPos.x, tPos.y);
		//SDL_Log("Direction <%f, %f>\n", fdir.x, fdir.y);
		//SDL_Log("Rotation <%f>", r);
		//SDL_Log("\n\n");
}

void Player::move(){
		float normalize = 1;
		if (inpt.x != 0 && inpt.y != 0)
				normalize = std::sqrt( std::pow(inpt.x,2) + std::pow(inpt.y,2) );

		pos.x += (sdir.x * (inpt.x/normalize)  + fdir.x * (inpt.y/normalize)) * (deltaTime/2) * speed;
		pos.y += (fdir.y * (inpt.y/normalize)  + sdir.y * (inpt.x/normalize)) * (deltaTime/2) * speed;

		tPos.x = std::floor(pos.x / cSize)* cSize;
		tPos.y = std::floor(pos.y / cSize) * cSize;
}

void Player::draw(SDL_Renderer* renderer){
		SDL_FRect rect{
				static_cast<float>(pos.x - hCSize),
				static_cast<float>(pos.y - hCSize),
				static_cast<float>(cSize),
				static_cast<float>(cSize)
		};

		SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
		//if (texture == nullptr)
				SDL_RenderRect(renderer, &rect);
		//else
		//		texture->render(renderer, pos.x - hCSize, pos.y - hCSize, cSize, cSize);

		
		//DIRECTION DEBUG
		/*
		SDL_SetRenderDrawColor(renderer, 0x00, 0xFF, 0x00, 0xFF);
		SDL_RenderLine(renderer, 
						pos.x, 
						pos.y, 
						pos.x + (fdir.x * 20), 
						pos.y + (fdir.y * 20));


		SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
		SDL_RenderLine(renderer, 
						pos.x, 
						pos.y, 
						pos.x + (sdir.x * 10), 
						pos.y + (sdir.y * 10));
		*/

}


void Player::vision(SDL_Renderer* renderer){
		
		float HFV = FOV / 2.0;		
		double INCTR = OBSIDIANPI/180;

		//for (float i = r - HFV * INCTR; i < r + HFV * INCTR; i += INCTR){
		for (float i = r; i < r + 1; i ++){
				vec2 endPoint;
				vec2 snappedEndPoint;
				bool stop = false;
				for (int d = 1; d < renderDistance + 1; d++){
	
						endPoint.x = std::cos(i) * (cSize * d) + pos.x;
						endPoint.y = std::sin(i) * (cSize * d ) + pos.y;


						snappedEndPoint.y = (int)(endPoint.y / cSize) * cSize;
						if (demoMap[snappedEndPoint.y/cSize][(int)endPoint.x/cSize] == 1){
								SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
								SDL_RenderLine(renderer, pos.x, pos.y, endPoint.x, snappedEndPoint.y);
								break;
						}else{
								SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
								SDL_RenderLine(renderer, pos.x, pos.y, endPoint.x, endPoint.y);
						}
						

						/*
						endPoint.x = std::cos(i) * (cSize * d) + pos.x;
						endPoint.y = std::sin(i) * (cSize * d ) + pos.y;

						snappedEndPoint.x = (int)((endPoint.x) / cSize) * cSize;
						snappedEndPoint.y = (int)((endPoint.y) / cSize) * cSize;	
						
						if (demoMap[(int)snappedEndPoint.y / cSize][(int)snappedEndPoint.x / cSize] == 1){
								SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
								SDL_RenderLine(renderer, pos.x, pos.y, snappedEndPoint.x, snappedEndPoint.y);
								stop = true;
								break;
						}*/
				}
				
				/*if (!stop){
						SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
						SDL_RenderLine(renderer, pos.x, pos.y, endPoint.x, endPoint.y);
		
				}*/
		}


}


Player::Player(){
		pos.x = 250; pos.y = 250; 
		texture = &textures.find("Player")->second;
}

Player::~Player(){
		texture = nullptr;
}
