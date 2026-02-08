#include "cell.h"

void Cell::setTexture(Texture* texture){
		this->texture = texture;
}

void Cell::draw(SDL_Renderer* renderer, float x, float y){
		texture->render(renderer, x, y, cSize, cSize);
		//SDL_SetRenderDrawColor(renderer,0xff,0xff,0xff,0xff);

		mesh = {x, y, cSize, cSize};
		//SDL_RenderRect(renderer,&mesh);
}

std::string Cell::getTName(){ return tName; }

Cell::Cell(std::string tName){
		this->texture = nullptr;
		this->tName = tName;
		
}

Cell::~Cell(){
		texture = nullptr;
}
