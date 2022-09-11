#include "GameLogic.hpp"

using namespace gamelogic;

int totalScore = 0;
eTileValue tileValue[MATRIX_SIZE][MATRIX_SIZE];

void gamelogic::Initialize()
{
	for (int row = 0; row < MATRIX_SIZE; row++)
	{
		for (int column = 0; column < MATRIX_SIZE; column++)
		{
			tileValue[row][column] = eTileValue::Tile0;
		}
	}

	CreateTileValue();
	CreateTileValue();
}

void gamelogic::CreateTileValue()
{
	srand((unsigned int)time(NULL));
	unsigned int row = rand() % MATRIX_SIZE;
	unsigned int column = rand() % MATRIX_SIZE;

	while (tileValue[row][column] != eTileValue::Tile0)
	{
		row = rand() % MATRIX_SIZE;
		column = rand() % MATRIX_SIZE;
	}

	tileValue[row][column] = eTileValue::Tile2;
}

void gamelogic::Rotate90()
{
	eTileValue newTileValue[MATRIX_SIZE][MATRIX_SIZE];

	for (int row = 0; row < MATRIX_SIZE; row++)
	{
		for (int column = 0; column < MATRIX_SIZE; column++)
		{
			newTileValue[column][row] = tileValue[row][column];
		}
	}

	// 회전 적용
	for (int row = 0; row < MATRIX_SIZE; row++)
	{
		for (int column = 0; column < MATRIX_SIZE; column++)
		{
			tileValue[row][column] = newTileValue[row][column];
			std::cout << (unsigned int)tileValue[row][column];
		}
		std::cout << std::endl;
	}
}

void gamelogic::Sort()
{
	eTileValue newTileValue[MATRIX_SIZE][MATRIX_SIZE];



}

void gamelogic::Merge()
{

}