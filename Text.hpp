#pragma once

#include <string>
#include <SDL.h>

#include "TextureManager.hpp"

class Text
{
public:
	Text(int xPos, int yPos);
	Text(const char* endText);
	~Text();

	void Update();
	void Render();

private:
	int scoreText;

	SDL_Texture* textTexture;
	SDL_Rect destRect;

	TTF_Font* textFont;
	SDL_Color textFontColor;
};
