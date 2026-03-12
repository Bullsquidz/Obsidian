#include "player/player.h"
#include "map/map.h"
#include "base/obsidian.h"
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
				case SDLK_E: r += OPI/18; break;
				case SDLK_Q: r -= OPI/18; break;
		}
		if ( r > (2 * OPI) )
				r =  0;
		else if ( r < 0 )
				r = 2*OPI;



		fdir.x = std::cos(r);
		fdir.y = std::sin(r);
		sdir.x = -std::sin(r);
		sdir.y = std::cos(r);

		//SDL_Log("Input  <%d, %d>\n", pos.x, pos.y);
		//SDL_Log("Position  <%d, %d>\n", pos.x, pos.y);
		//SDL_Log("T.Position(OnGrid) <%d, %d>\n", tPos.x/cSize, tPos.y/cSize);
		//SDL_Log("Direction <%f, %f>\n", fdir.x, fdir.y);
		//SDL_Log("Rotation <%f>", r);
		//SDL_Log("\n\n");
}

void Player::move(){
		float normalize = 1;
		if (inpt.x != 0 && inpt.y != 0)
				normalize = std::sqrt( std::pow(inpt.x,2) + std::pow(inpt.y,2) );

		pos.x += (sdir.x * (inpt.x/normalize)  + fdir.x * (inpt.y/normalize)) * (deltaTime/2) * speed * cScale;
		pos.y += (fdir.y * (inpt.y/normalize)  + sdir.y * (inpt.x/normalize)) * (deltaTime/2) * speed * cScale;

		tPos.x = std::floor(pos.x / cSize) * cSize;
		tPos.y = std::floor(pos.y / cSize) * cSize;


}

int playerBoxSize = hCSize;
int halfPlayerBoxSize = playerBoxSize/2;
void Player::draw(SDL_Renderer* renderer){
		SDL_FRect rect{
				static_cast<float>(pos.x - halfPlayerBoxSize),
				static_cast<float>(pos.y - halfPlayerBoxSize),
				static_cast<float>(playerBoxSize),
				static_cast<float>(playerBoxSize)
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
		double INCTR = OPI/180;

		//for (float i = r - HFV * INCTR; i < r + HFV * INCTR; i += INCTR){
		for (float i = r; i < r + 1; i ++){
				fvec2 prevRayPoint;
				fvec2 rayPoint;
				//rayPoint.x = pos.x;
				//rayPoint.y = pos.y;
				
				vec2 prevCellPoint;
				fvec2 cellPoint;

				SDL_SetRenderDrawColor(renderer, 
										0xFF, 
										0x00, 
										0x00, 
										0xFF);
				int Ya = 0;
				if (r > OEPSI && r < OPI - OEPSI) {//Ray down
						Ya = cSize;
						cellPoint.y = (int)(pos.y / cSize) * cSize + cSize + OEPSI;
				}
				else if (r > OPI + OEPSI && r < 2 * OPI - OEPSI) {
						Ya = -cSize;
						cellPoint.y = (int)(pos.y / cSize) * cSize - OEPSI;
				} else{
						continue;
				}

				cellPoint.x = pos.x + -(pos.y - cellPoint.y)/tan(r);
				float Xa = Ya /tan(r);

				SDL_Log("%f,%f", cellPoint.x, cellPoint.y);
				if (cellPoint.x < 0) {cellPoint.x = 0;}
				//else if (cellPoint.x > MAPSIZE-1) cellPoint.x = MAPSIZE-1;

				//if (cellPoint.y < 0) cellPoint.y = 0;
				//else if (cellPoint.y > MAPSIZE-1) cellPoint.y = MAPSIZE-1;

				if (demoMap[(int)cellPoint.y / cSize][(int)cellPoint.x / cSize] == 1) {
						SDL_SetRenderDrawColor(renderer, 0x00, 0xCC, 0x00, 0xFF);

						SDL_RenderLine(renderer, 
										pos.x, pos.y, 
										cellPoint.x, cellPoint.y);

						continue;
				}
				
				/*
				for (int d = 1; d< renderDistance + 1; d++){
						cellPoint.x += Xa;
						cellPoint.y += Ya;

						if (cellPoint.x < 0) cellPoint.x = 0;
						else if (cellPoint.x > MAPSIZE-1) cellPoint.x = MAPSIZE-1;

						if (cellPoint.y < 0) cellPoint.y = 0;
						else if (cellPoint.y > MAPSIZE-1) cellPoint.y = MAPSIZE-1;
		
						if (demoMap[(int)cellPoint.y / cSize][(int)cellPoint.x / cSize] == 1) {
								SDL_SetRenderDrawColor(renderer, 0x00, 0xCC, 0x00, 0xFF);
								break;
						}
				}



				SDL_RenderLine(renderer, 
										pos.x, pos.y, 
										cellPoint.x, cellPoint.y);
				SDL_Log("%d,%d", (int)cellPoint.x / cSize, (int)cellPoint.y / cSize);
				*/


				//for (int d = 1; d < renderDistance + 1; d++){

						//prevRayPoint.x = rayPoint.x;
						//prevRayPoint.y = rayPoint.y;

						//rayPoint.x = std::cos(i) * (cSize * d) + pos.x;
						//rayPoint.y = std::sin(i) * (cSize * d) + pos.y;

						/*SDL_SetRenderDrawColor(renderer, 
										0x22 * d, 
										0xFF - (0x22 * d), 
										0x00, 
										0xFF);

						SDL_RenderLine(renderer, 
										prevRayPoint.x, prevRayPoint.y, 
										rayPoint.x, rayPoint.y);
*/

						//cellPoint.x = (int)(rayPoint.x / cSize);
						//cellPoint.y = (int)(rayPoint.y / cSize);

						//if (demoMap[cellPoint.x][cellPoint.y] == 1){


/*
						snappedEndPoint.y = (int)(endPoint.y / cSize) * cSize;
						if (demoMap[snappedEndPoint.y/cSize][(int)endPoint.x/cSize] == 1){
								SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
								SDL_RenderLine(renderer, pos.x, pos.y, endPoint.x, endPoint.y);
								break;
						}else{
								SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
								SDL_RenderLine(renderer, pos.x, pos.y, endPoint.x, endPoint.y);
						}
						
*/
						/*if (std::tan(r) != 0){//UP N DOWN
						
						}*/
/*
						if ((r > OBSIDIONEPSILON && r < OBSIDIANPI - OBSIDIONEPSILON) ||
								(r > OBSIDIANPI + OBSIDIONEPSILON && r < 2 * OBSIDIANPI - OBSIDIONEPSILON) ){ //UP N DOWN


						}

*/








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
				//}
				
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
