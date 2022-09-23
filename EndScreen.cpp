#include "EndScreen.hpp"

EndScreen::EndScreen(const char* textureSheet) : GameObject(textureSheet)
{
	srcRect.w = END_SCREEN_WIDTH;
	srcRect.h = END_SCREEN_HEIGHT;

	srcRect.x = 0;
	srcRect.y = 0;

	destRect.w = END_SCREEN_WIDTH;
	destRect.h = END_SCREEN_HEIGHT;
	destRect.x = xPos;
	destRect.y = yPos;
}

EndScreen::~EndScreen()
{

}