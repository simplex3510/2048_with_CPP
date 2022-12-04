#include "GameLogic.hpp"

using namespace gamelogic;

int totalScore = 0;
eTileValue tileValue[MATRIX_SIZE][MATRIX_SIZE];

int tileValueCnt = 0; //���� ��� Ÿ�Ͽ� ���� �ִ���(=Ÿ���� ���� á����) Ȯ��. ���ӿ��� ���� üũ�� ���.
int isMergedCnt = 0; //���� �� �� �ִ� Ÿ���� �ִ��� ���� Ȯ��. ���ӿ��� ���� üũ�� ���.

void gamelogic::Initialize()
{
	for (int row = 0; row < MATRIX_SIZE; row++)
	{
		for (int column = 0; column < MATRIX_SIZE; column++)
		{
			tileValue[row][column] = eTileValue::Tile1;
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

	while (tileValue[row][column] != eTileValue::Tile1)
	{
		row = rand() % MATRIX_SIZE;
		column = rand() % MATRIX_SIZE;
	}

	tileValue[row][column] = eTileValue::Tile2048;
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
			newTileValue[row][column] = eTileValue::Tile1; 
		}
	}
	// done = true;

	for (int row = 0; row < MATRIX_SIZE; row++)
	{
		int count = 0;
		for (int column = 0; column < MATRIX_SIZE; column++)
		{

			if (tileValue[row][column] != eTileValue::Tile1)
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
			if (tileValue[row][column] != newTileValue[row][column])
			{
				tileValue[row][column] = newTileValue[row][column];
				movedCnt++;
			}
		}
	}

	return movedCnt;
}

int gamelogic::Merge()
{
	int createdTile = -1;		// Ÿ�� ������ Ƚ��. Merge()�� ���ϰ�.
	bool is0 = false;		// ������ Ÿ���� 0 Ÿ������ Ȯ��.

	for (int row = 0; row < MATRIX_SIZE; row++)
	{
		for (int column = 0; column < MATRIX_SIZE - 1; column++)
		{
			if (tileValue[row][column] == tileValue[row][column + 1] && tileValue[row][column] != eTileValue::Tile1)
			{
				switch (tileValue[row][column])
				{
				case eTileValue::Tile2048:
					tileValue[row][column] = eTileValue::Tile1024;
					break;
				case eTileValue::Tile1024:
					tileValue[row][column] = eTileValue::Tile512;
					break;
				case eTileValue::Tile512:
					tileValue[row][column] = eTileValue::Tile256;
					break;
				case eTileValue::Tile256:
					tileValue[row][column] = eTileValue::Tile128;
					break;
				case eTileValue::Tile128:
					tileValue[row][column] = eTileValue::Tile64;
					break;
				case eTileValue::Tile64:
					tileValue[row][column] = eTileValue::Tile32;
					break;
				case eTileValue::Tile32:
					tileValue[row][column] = eTileValue::Tile16;
					break;
				case eTileValue::Tile16:
					tileValue[row][column] = eTileValue::Tile8;
					break;
				case eTileValue::Tile8:
					tileValue[row][column] = eTileValue::Tile4;
					break;
				case eTileValue::Tile4:
					tileValue[row][column] = eTileValue::Tile2;
					break;
				case eTileValue::Tile2:
					tileValue[row][column] = eTileValue::Tile0;
					is0 = true;
					break;
				default:
					break;
				}
				tileValue[row][column+1] = eTileValue::Tile1;
				createdTile = (int)tileValue[row][column];
				totalScore += (unsigned int)tileValue[row][column];
				// done = true;
			}
		}
	}

	if (is0)
	{
		createdTile = 1;
	}

	return createdTile;
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

bool gamelogic::CheckGameOver()
{
	tileValueCnt = 0; 
	isMergedCnt = 0;

	for (int row = 0; row < MATRIX_SIZE; row++)
	{
		for (int column = 0; column < MATRIX_SIZE; column++)
		{
			//Ÿ�� �ȿ� 1�� �ƴ� ���� ������(= ������� ������) ī��Ʈ �÷��ֱ� 
			if (tileValue[row][column] != eTileValue::Tile1) 
			{
				tileValueCnt++; 
			}

			//���� ���� ��ҿ� �ٷ� �����ʿ� �ִ� ��Ұ� ���� �����ϴٸ� ī��Ʈ �÷��ֱ�
			//��. ���� ��Ұ� �� ������ ���̶�� �� ���� �ʰ� �ϱ�
			if (tileValue[row][column] == tileValue[row][column + 1] && column + 1 < MATRIX_SIZE)
			{
				isMergedCnt++;
			}
			//���� ���� ��ҿ� �ٷ� �Ʒ��� �ִ� ��Ұ� ���� �����ϴٸ� ī��Ʈ �÷��ֱ�
			//��. ���� ��Ұ� �� �Ʒ����̶�� �� ���� �ʰ� �ϱ�
			if (tileValue[row][column] == tileValue[row + 1][column] && row+1<MATRIX_SIZE)
			{
				isMergedCnt++;
			}
		}
	}
	/* �� �����Ӹ��� 0�� �ƴ� ���� ����ִ� Ÿ�� ������ ���� ������ Ƚ�� ���.
	std::cout << "tileValueCnt: " << tileValueCnt << std::endl; //16 (=Ÿ�� �� �� ����) �̰�
	std::cout << "isMergedCnt: " << isMergedCnt << std::endl;  //0 (=���� �� �� ����) ���� ��µǸ� ���ӿ���. 
	*/

	if (tileValueCnt == MATRIX_SIZE * MATRIX_SIZE && isMergedCnt == 0) //Ÿ���� �� á��, ������ �� �ִ� ��ҵ� ������
	{
		return true; //���� ����
	}
	else //�ƴϸ�
	{
		return false; //��� ���� 
	}
}

void gamelogic::DeleteBigNumber()
{
	for (int row = 0; row < MATRIX_SIZE; row++)
	{
		for (int column = 0; column < MATRIX_SIZE; column++)
		{
			if (tileValue[row][column] >= eTileValue::Tile512)
			{
				tileValue[row][column] = eTileValue::Tile1;
			}
		}
	}
}
