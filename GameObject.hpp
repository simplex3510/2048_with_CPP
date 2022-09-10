#pragma once

#include <SDL.h>

class GameObject abstract
{
public:
	GameObject(const char* textureSheet, int x, int y);
	~GameObject();

	void Update();
	void Render();

protected:
	int xPos;
	int yPos;

	SDL_Texture* objectTexture;
	SDL_Rect srcRect, destRect;
};