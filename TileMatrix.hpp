#pragma once

#include <SDL.h>

#include "Tile.hpp"

#define MATRIX_SIZE 4

class TileMatrix
{
public:
	TileMatrix();
	~TileMatrix();

	void LoadTile();
	void DrawTile();

protected:
	int xPos;
	int yPos;

private:
	Tile* tileMatrix[MATRIX_SIZE][MATRIX_SIZE];

	SDL_Rect srcRect, destRect;
};