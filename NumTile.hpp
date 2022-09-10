#pragma once

#include "Tile.hpp"

class NumTile : public Tile
{
public:
	NumTile();
	~NumTile();

private:
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

