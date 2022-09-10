#include "Background.hpp"

Background::Background(const char* textureSheet, int xPos, int yPos, int width, int height) : GameObject(textureSheet, xPos, yPos)
{
	srcRect.h = GAME_HEIGHT;
	srcRect.w = GAME_WIDTH;

	srcRect.x = 0;
	srcRect.y = 0;

	destRect.h = height;
	destRect.w = width;
	destRect.x = xPos;
	destRect.y = yPos;
}

Background::~Background()
{
}