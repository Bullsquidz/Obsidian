#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>
#include <SDL3_image/SDL_image.h>

class Texture{
	public:
		Texture(std::string path);
		~Texture();

		void destroyTexture();
		bool loadFromFile(SDL_Renderer* gameRenderer);
		void render(SDL_Renderer* gameRenderer, float x, float y, int w = -1, int h = -1);
		
		int getWidth();
		int getHeight();
		bool isLoaded();
		SDL_Texture* getTexture();

	private:
		SDL_Texture* texture;
		int width;
		int height;
		std::string path;
};


#endif
