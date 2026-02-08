#include "texture.h"

Texture::Texture(std::string path){
	texture = nullptr;
	width = 0;
	height = 0;
	this->path = path;
};
SDL_Texture* Texture::getTexture(){ return texture; }

Texture::~Texture(){
	destroyTexture();
};

void Texture::destroyTexture(){
	SDL_DestroyTexture(texture);
	texture = nullptr;
	width = 0;
	height = 0;
}

bool Texture::loadFromFile(SDL_Renderer* gameRenderer){
	destroyTexture();

	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == nullptr){
		SDL_Log("Unable to load image %s! Error: %s\n", path.c_str(), SDL_GetError());
	}else{

		texture = SDL_CreateTextureFromSurface(gameRenderer, loadedSurface);
		if (texture == nullptr){
			SDL_Log("Unable to create texture from loadedSurface! Error: %s\n", SDL_GetError());
		}else{
			width = loadedSurface->w;
			height = loadedSurface->h;
		}

		SDL_DestroySurface(loadedSurface);
	}

	return texture != nullptr;
} 

void Texture::render(SDL_Renderer* gameRenderer, float x, float y, int w, int h){
	if (w == -1 && h == -1){
		w = width; h = height;
	}
	SDL_FRect dstRect{x, y, static_cast<float>(w), static_cast<float>(h)};
	SDL_RenderTexture(gameRenderer, texture, nullptr, &dstRect);
}

int Texture::getWidth()  { return width; }
int Texture::getHeight() { return height; }
bool Texture::isLoaded() { return texture != nullptr; }

