#include "TextureManager.hpp"

TextureManager::TextureManager()
{
}

TextureManager::~TextureManager()
{
}

SDL_Texture* TextureManager::LoadTexture(const char* fileName)
{
	SDL_Surface* tempSurface = IMG_Load(fileName);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(WindowManager::renderer, tempSurface);

	SDL_FreeSurface(tempSurface);

	return texture;
}