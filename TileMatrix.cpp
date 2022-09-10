#include "TileMatrix.hpp"
#include "TextureManager.hpp"

TileMatrix::TileMatrix()
{
	LoadTile();
}

TileMatrix::~TileMatrix()
{
}

void TileMatrix::LoadTile()
{
	for (int row = 0; row < MAP_SIZE; row++)
	{
		for (int column = 0; column < MAP_SIZE; column++)
		{
			tileMatrix[row][column] = new Tile();
		}
	}
}

void TileMatrix::DrawTile(int value)
{
	for (int row = 0; row < MAP_SIZE; row++)
	{
		for (int column = 0; column < MAP_SIZE; column++)
		{
			tileMatrix[row][column]->destRect.x = 410 + 15 + 110 * column;
			tileMatrix[row][column]->destRect.y = 220 + 15 + 110 * row;
			tileMatrix[row][column]->DrawTile(0);
		}
	}
}
