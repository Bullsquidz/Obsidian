#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h>
#include <map>
#include <string>
#include "texture.h"
#include "obsidian.h"
#include "player.h"

SDL_Window *window = nullptr;
SDL_Renderer *renderer = nullptr;

std::map<std::string, Texture> textures{
	{ "Wall", Texture("wall.png") }
};



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

bool initTexture(){
		for( auto& entry : textures){
				if (!entry.second.loadFromFile(renderer)){
						SDL_Log("Texture {%s} failed to load!\n", entry.first.c_str());
						return false;
				}
		}

		return true;
}

void desTexture(){
		for (auto& entry : textures){
				entry.second.destroyTexture();
		}
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

		if (!initTexture())
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
				SDL_SetRenderDrawColor(renderer, 20, 50, 100, 255);
				SDL_RenderClear(renderer);

				player.draw(renderer);

				SDL_RenderPresent(renderer);
				timeWizard.frameCap();
		}

		SDL_Log("Terminating Program!\n");
		close();

		return 0;

}








