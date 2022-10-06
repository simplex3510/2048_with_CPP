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

	CreateNewTile();
	CreateNewTile();
}

void gamelogic::CreateNewTile()
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
		for (int column = 0, newColumn = MATRIX_SIZE - 1; -1 < newColumn; column++, newColumn--)
		{
			newTileValue[row][column] = tileValue[newColumn][row];
		}
	}

	// ȸ�� ����
	for (int row = 0; row < MATRIX_SIZE; row++)
	{
		for (int column = 0; column < MATRIX_SIZE; column++)
		{
			tileValue[row][column] = newTileValue[row][column];
		}
	}
}

int gamelogic::Sort()
{
	int movedCnt = 0;	// Ÿ�� �̵� Ƚ��. Sort()�� ���ϰ�.
	eTileValue newTileValue[MATRIX_SIZE][MATRIX_SIZE];
	for (int row = 0; row < MATRIX_SIZE; row++)
	{
		for (int column = 0; column < MATRIX_SIZE; column++)
		{
			newTileValue[row][column] = eTileValue::Tile0;
		}
	}
	// done = true;

	for (int row = 0; row < MATRIX_SIZE; row++)
	{
		int count = 0;
		for (int column = 0; column < MATRIX_SIZE; column++)
		{

			if (tileValue[row][column] != eTileValue::Tile0)
			{
				newTileValue[row][count] = tileValue[row][column];

				if (column != count)
				{
					// done = false;
				}

				count++;
			}
		}
	}

	// ���� ����
	for (int row = 0; row < MATRIX_SIZE; row++)
	{
		for (int column = 0; column < MATRIX_SIZE; column++)
		{
			if (tileValue[row][column] != newTileValue[row][column]) {
				tileValue[row][column] = newTileValue[row][column];
				movedCnt++;
			}
		}
	}

	return movedCnt;
}

int gamelogic::Merge()
{
	int mergedCnt = 0;		// Ÿ�� ������ Ƚ��. Merg()�� ���ϰ�.
	bool is2048 = false;	// ������ Ÿ���� 2048 Ÿ������ Ȯ��.

	// done = false
	for (int row = 0; row < MATRIX_SIZE; row++)
	{
		for (int column = 0; column < MATRIX_SIZE - 1; column++)
		{
			if (tileValue[row][column] == tileValue[row][column + 1] && tileValue[row][column] != eTileValue::Tile0)
			{
				switch (tileValue[row][column])
				{
				case eTileValue::Tile2:
					tileValue[row][column] = eTileValue::Tile4;
					break;
				case eTileValue::Tile4:
					tileValue[row][column] = eTileValue::Tile8;
					break;
				case eTileValue::Tile8:
					tileValue[row][column] = eTileValue::Tile16;
					break;
				case eTileValue::Tile16:
					tileValue[row][column] = eTileValue::Tile32;
					break;
				case eTileValue::Tile32:
					tileValue[row][column] = eTileValue::Tile64;
					break;
				case eTileValue::Tile64:
					tileValue[row][column] = eTileValue::Tile128;
					break;
				case eTileValue::Tile128:
					tileValue[row][column] = eTileValue::Tile256;
					break;
				case eTileValue::Tile256:
					tileValue[row][column] = eTileValue::Tile512;
					break;
				case eTileValue::Tile512:
					tileValue[row][column] = eTileValue::Tile1024;
					break;
				case eTileValue::Tile1024:
					tileValue[row][column] = eTileValue::Tile2048;
					is2048 = true;
					break;
				default:
					break;
				}
				tileValue[row][column+1] = eTileValue::Tile0;
				mergedCnt++;
				totalScore += (unsigned int)tileValue[row][column];
				// done = true;
			}
		}
	}
	if (is2048) { mergedCnt = 2048; }

	return mergedCnt;
}

void gamelogic::PrintTileValueMatrix()
{
	std::cout << "����������������������������������������������������������������������������������" << std::endl;
	for (int row = 0; row < MATRIX_SIZE; row++)
	{
		for (int column = 0; column < MATRIX_SIZE; column++)
		{
			std::cout << (unsigned int)tileValue[row][column] << "  ";
		}
		std::cout << std::endl;
	}
}