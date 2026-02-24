#include "textureTown.h"

std::map<std::string, Texture> textures{
		{ "Wall", 	Texture("test.png") 	},
		{ "Player",	Texture("player.png")	}
};

bool initTexture(SDL_Renderer* renderer){
		for( auto& entry : textures){
				if (!entry.second.loadFromFile(renderer)){
						SDL_Log("Texture {%s} failed to load!\n", entry.first.c_str());
						return false;
				}
				SDL_Log("Texture {%s} loaded.\n", entry.first.c_str());
		}

		return true;
}

void desTexture(){
		for (auto& entry : textures){
				entry.second.destroyTexture();
		}
}

