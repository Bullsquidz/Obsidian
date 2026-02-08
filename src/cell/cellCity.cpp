#include "cellCity.h"

std::map<std::string, Cell> cells{
		{ "Wall", Cell("Wall")}
};

bool initCells(){
		for(auto& entry : cells){
				auto cur = textures.find(entry.second.getTName()); 
				if (cur == textures.end()){
						SDL_Log("Cell {%s} failed to instantiate! Bad Texture Name\n", entry.first.c_str());
						return false;
				}
				entry.second.setTexture(&cur->second);
				SDL_Log("Cell {%s} instantiated.\n", entry.first.c_str());
		}
		return true;
}


