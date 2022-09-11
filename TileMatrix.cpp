#include "TileMatrix.hpp"
#include "TextureManager.hpp"

#include "GameLogic.hpp"

using namespace gamelogic;

TileMatrix::TileMatrix()
{
	LoadTile();

	Initialize();
}

TileMatrix::~TileMatrix()
{
}

void TileMatrix::LoadTile()
{
	for (int row = 0; row < MATRIX_SIZE; row++)
	{
		for (int column = 0; column < MATRIX_SIZE; column++)
		{
			tileMatrix[row][column] = new Tile();
		}
	}
}

void TileMatrix::DrawTile()
{
	for (int row = 0; row < MATRIX_SIZE; row++)
	{
		for (int column = 0; column < MATRIX_SIZE; column++)
		{
			tileMatrix[row][column]->destRect.x = 410 + 15 + 110 * column;
			tileMatrix[row][column]->destRect.y = 220 + 15 + 110 * row;
			tileMatrix[row][column]->DrawTile(tileValue[row][column]);
		}
	}
}
