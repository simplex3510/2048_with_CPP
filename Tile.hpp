#pragma once

#include <SDL.h>

#include "ETileValue.hpp"

class Tile
{
public:
	Tile();
	~Tile();

	void LoadTile();
	void DrawTile(eTileValue value);

	SDL_Texture* texture;
	SDL_Rect srcRect, destRect;

private:
	int xPos, yPos;

	SDL_Texture* tile0;
	SDL_Texture* tile2;
	SDL_Texture* tile4;
	SDL_Texture* tile8;
	SDL_Texture* tile16;
	SDL_Texture* tile32;
	SDL_Texture* tile64;
	SDL_Texture* tile128;
	SDL_Texture* tile256;
	SDL_Texture* tile512;
	SDL_Texture* tile1024;
	SDL_Texture* tile2048;
};

