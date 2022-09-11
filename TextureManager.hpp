#pragma once

#include "SingletonBase.hpp"
#include "WindowManager.hpp"

class TextureManager : public SingletonBase<TextureManager>
{
public:
	TextureManager();
	~TextureManager();

	static SDL_Texture* LoadTexture(const char* fileName);
	static SDL_Texture* LoadTextTexture(TTF_Font* textFont, const char* text, SDL_Color* fontColor, SDL_Rect* destRect);
	static void Draw(SDL_Texture* texture, SDL_Rect srcRect, SDL_Rect destRect);

private:

};
