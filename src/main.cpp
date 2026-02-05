#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h>

const int ScreenWidth = 500, ScreenHeight = 500;

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

	SDL_Quit();
}

int main(){
	if (!init()){
		SDL_Log("Cant initialize project!\n");
		return 1;
	}

	SDL_Event e;
	SDL_zero(e);

	bool quit = false;
	while(!quit){
		while(SDL_PollEvent(&e)){
			if (e.type == SDL_EVENT_QUIT){
				quit = true;
			}
		}

		SDL_SetRenderDrawColor(renderer, 20, 50, 100, 255);
		SDL_RenderClear(renderer);
		SDL_RenderPresent(renderer);

	}

	SDL_Log("Terminating Program!\n");
	close();

	return 0;

}








