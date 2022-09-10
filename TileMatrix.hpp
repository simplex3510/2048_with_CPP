#pragma once

#include <SDL.h>

#include "Tile.hpp"

#define MAP_SIZE 4

class TileMatrix
{
public:
	TileMatrix();
	~TileMatrix();

	void LoadTile();
	void DrawTile(int value);

protected:
	int xPos;
	int yPos;

private:
	Tile* tileMatrix[MAP_SIZE][MAP_SIZE];

	SDL_Rect srcRect, destRect;
};