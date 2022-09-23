#pragma once

#include "GameObject.hpp"

#define END_SCREEN_WIDTH  1280
#define END_SCREEN_HEIGHT 720

class EndScreen : public GameObject
{
public:
	EndScreen(const char* textureSheet);
	~EndScreen();

private:

};