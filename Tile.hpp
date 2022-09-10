#pragma once

#include <SDL.h>

#define MAP_SIZE 4

class Tile
{
public:
	SDL_Texture* tileTexture;
	SDL_Rect srcRect, destRect;

	Tile();
	Tile(const char* textureSheet);
	~Tile();

	virtual void DrawTile();
	int  getValue();
	void setValue(int value);

protected:
	int value;

	int xPos;
	int yPos;

};