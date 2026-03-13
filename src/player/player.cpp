#include "player/player.h"
#include "map/map.h"
#include "base/obsidian.h"
#include "base/timeWizard.h"

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
						case SDLK_MINUS: FOV -= 10; break;
						case SDLK_PLUS: FOV += 10; break;
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

int MAXMAPBOUND = (MAPSIZE-1)*cSize;
void Player::outOfBoundsVision(fvec2& cellPoint) {
				if (cellPoint.x < 0) cellPoint.x = 0;
				else if (cellPoint.x > MAXMAPBOUND)  cellPoint.x = MAXMAPBOUND;

				if (cellPoint.y < 0) cellPoint.y = 0;
				else if (cellPoint.y > MAXMAPBOUND) cellPoint.y = MAXMAPBOUND;
}

bool Player::checkVision(fvec2& cellPoint, SDL_Renderer* renderer){
		if (demoMap[(int)cellPoint.y / cSize][(int)cellPoint.x / cSize] == 1){
				return true;
		}
		return false;
}

void Player::vision(SDL_Renderer* renderer){
		
		float HFV = FOV / 2.0;		
		double INCTR = OPI/180;
		
		//for (float i = r; i < r+1; i++){
		for (float i = r - HFV * INCTR; i < r + HFV * INCTR; i += INCTR){
				fvec2 hCellPoint; hCellPoint.x = -1; hCellPoint.y = -1;
				bool hFound = false;
				fvec2 vCellPoint; vCellPoint.x = -1; vCellPoint.y = -1;
				bool vFound = false;

				float iAngle = i;
				if (iAngle < 0) iAngle += 2*OPI;
				if (iAngle > 2*OPI) iAngle -= 2*OPI;


				//HORIZONTOLLYYY
				//
				float Ya = 0;
				if (iAngle > 0 && iAngle < OPI) {//Ray down
						Ya = cSize;
						hCellPoint.y = (int)(pos.y / cSize) * cSize + cSize + OEPSI;
				}
				else if (iAngle > OPI && iAngle < 2 * OPI) {
						Ya = -cSize;
						hCellPoint.y = (int)(pos.y / cSize) * cSize - OEPSI;
				} else continue;

				hCellPoint.x = pos.x + ( hCellPoint.y - pos.y)/tan(iAngle);
				float Xa = Ya /tan(iAngle);

				for (int d = 1; d< renderDistance + 1; d++){
						outOfBoundsVision(hCellPoint);
						hFound = checkVision(hCellPoint, renderer);
						if (hFound) break;

						hCellPoint.x += Xa;
						hCellPoint.y += Ya;
				}

				//SDL_Log("\n\n\n");
				//SDL_Log("HORZ (Y): [%d, %d]", (int)hCellPoint.x / cSize, (int)hCellPoint.y/cSize);



				//VERTIALLIALY
				//
				if (iAngle > OPI/2 && iAngle < (3*OPI) / 2) {//Ray LEFT
						Xa = -cSize;
						vCellPoint.x = (int)(pos.x / cSize) * cSize - OEPSI;
				}
				else if (iAngle > (3*OPI) / 2 || iAngle < OPI/2) {
						Xa = cSize;
						vCellPoint.x = (int)(pos.x / cSize) * cSize + cSize + OEPSI;
				} else continue;


				vCellPoint.y = pos.y + (vCellPoint.x - pos.x) * tan(iAngle);
				Ya = Xa * tan(iAngle);

				for (int d = 1; d< renderDistance + 1; d++){
						outOfBoundsVision(vCellPoint);
						vFound = checkVision(vCellPoint, renderer);
						if (vFound) break;

						vCellPoint.x += Xa;
						vCellPoint.y += Ya;
				}


						float hDistance = CalcDist(hCellPoint, pos);
						float vDistance = CalcDist(vCellPoint, pos);
						if (hDistance <= vDistance){
								if (hFound) {SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0xFF, 0xFF);
								//else SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x55, 0xFF);

								SDL_RenderLine(renderer, pos.x, pos.y, hCellPoint.x, hCellPoint.y);}
								continue;
						} else { 
								if (vFound) {SDL_SetRenderDrawColor(renderer, 0x00, 0xFF, 0x00, 0xFF);
								//else SDL_SetRenderDrawColor(renderer, 0x00, 0x55, 0x00, 0xFF);

								SDL_RenderLine(renderer, pos.x, pos.y, vCellPoint.x, vCellPoint.y);}
								continue;
						}




				//SDL_RenderLine(renderer, pos.x, pos.y, cellPoint.x, cellPoint.y);
		}


}


Player::Player(){
		pos.x = 250; pos.y = 250; 
		texture = &textures.find("Player")->second;
}

Player::~Player(){
		texture = nullptr;
}
