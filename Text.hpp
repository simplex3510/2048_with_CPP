#pragma once

#include <string>
#include <SDL.h>

#include "TextureManager.hpp"

class Text
{
public:
	Text();
	~Text();

	void Update();
	void Render();

private:
	int score;

	SDL_Texture* textTexture;
	SDL_Rect destRect;

	TTF_Font* textFont;
	SDL_Color textFontColor;
};

