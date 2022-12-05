#pragma once

#include <string>
#include <SDL.h>

#include "TextureManager.hpp"

class Text
{
public:
	Text(int xPos, int yPos);
	Text(const char* endText);
	Text(const char* tutorText, bool isTutorial); //튜토리얼 용 텍스트 출력
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
