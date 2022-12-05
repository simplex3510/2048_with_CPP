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

SDL_Texture* TextureManager::LoadTextTexture(TTF_Font* textFont, const char* text, SDL_Color* fontColor, SDL_Rect* destRect)
{
	//SDL_Surface* tempSurface = TTF_RenderText_Solid(textFont, text, *fontColor);
	SDL_Surface* tempSurface = TTF_RenderText_Blended_Wrapped(textFont, text, *fontColor, 400); //줄바꿈까지 포함
	SDL_Texture* texture = SDL_CreateTextureFromSurface(WindowManager::renderer, tempSurface);

	destRect->h = tempSurface->h;
	destRect->w = tempSurface->w;

	SDL_FreeSurface(tempSurface);

	return texture;
}

void TextureManager::Draw(SDL_Texture* texture, SDL_Rect srcRect, SDL_Rect destRect)
{
	SDL_RenderCopy(WindowManager::renderer, texture, &srcRect, &destRect);
}