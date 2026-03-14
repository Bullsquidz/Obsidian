#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h>

#include "obsidian.h"
#include "timeWizard.h"

#include "textureTown.h"
#include "cellCity.h"

#include "player.h"
#include "map.h"

SDL_Window *window = nullptr;
SDL_Renderer *renderer = nullptr;



bool init(){
	if (!SDL_Init(SDL_INIT_VIDEO)){
		SDL_Log("Couldnt init SDL: %s", SDL_GetError());
		return false;
	}
	if(!SDL_CreateWindowAndRenderer("Im not really sure", ScreenWidth, ScreenHeight, 0, &window, &renderer)){
		SDL_Log("Couldnt create window/renderer: %s", SDL_GetError());
		return false;
	}
	return true;	
}
void close(){
	SDL_DestroyRenderer(renderer);
	renderer = nullptr;
	SDL_DestroyWindow(window);
	window = nullptr;


	desTexture();

	SDL_Quit();
}

int main(){
		if (!init()){
				SDL_Log("Cant initialize project!\n");
				return 1;
		}

		if (!initTexture(renderer))
				return 2;

		if (!initCells())
				return 2;

		Player player;

		TimeWizard timeWizard;
		SDL_Event e;
		SDL_zero(e);
		bool quit = false;
		while(!quit){
				timeWizard.getCurTime();

				while(SDL_PollEvent(&e)){
						if (e.type == SDL_EVENT_QUIT){
								quit = true;
						}
						player.input(e);
				
				}

				//Physics
				player.move();

				//Draw
				SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
				SDL_RenderClear(renderer);

				//RAYCASTER
				player.vision(renderer);

				//2D DRAW
				if (showMap){
						drawMap(renderer);
						player.draw(renderer);
				}
				SDL_RenderPresent(renderer);
				timeWizard.frameCap();
		}

		SDL_Log("Terminating Program!\n");
		close();

		return 0;

}








