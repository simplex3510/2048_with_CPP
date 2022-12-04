#include "GameLogic.hpp"

using namespace gamelogic;

int totalScore = 0;
eTileValue tileValue[MATRIX_SIZE][MATRIX_SIZE];

int tileValueCnt = 0; //현재 몇개의 타일에 값이 있는지(=타일이 가득 찼는지) 확인. 게임오버 여부 체크에 사용.
int isMergedCnt = 0; //머지 할 수 있는 타일이 있는지 여부 확인. 게임오버 여부 체크에 사용.

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

	// 회전 적용
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
	int movedCnt = 0;	// 타일 이동 횟수. Sort()의 리턴값.
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

	// 정렬 적용
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
	int createdTile = -1;		// 타일 합쳐진 횟수. Merge()의 리턴값.
	bool is0 = false;		// 합쳐진 타일이 0 타일인지 확인.

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
	std::cout << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━" << std::endl;
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
			//타일 안에 1이 아닌 값이 있으면(= 비어있지 않으면) 카운트 늘려주기 
			if (tileValue[row][column] != eTileValue::Tile1) 
			{
				tileValueCnt++; 
			}

			//만약 현재 요소와 바로 오른쪽에 있는 요소가 머지 가능하다면 카운트 늘려주기
			//단. 현재 요소가 맨 오른쪽 줄이라면 비교 하지 않게 하기
			if (tileValue[row][column] == tileValue[row][column + 1] && column + 1 < MATRIX_SIZE)
			{
				isMergedCnt++;
			}
			//만약 현재 요소와 바로 아래에 있는 요소가 머지 가능하다면 카운트 늘려주기
			//단. 현재 요소가 맨 아랫줄이라면 비교 하지 않게 하기
			if (tileValue[row][column] == tileValue[row + 1][column] && row+1<MATRIX_SIZE)
			{
				isMergedCnt++;
			}
		}
	}
	/* 매 프레임마다 0이 아닌 값이 들어있는 타일 갯수와 머지 가능한 횟수 출력.
	std::cout << "tileValueCnt: " << tileValueCnt << std::endl; //16 (=타일 꽉 찬 상태) 이고
	std::cout << "isMergedCnt: " << isMergedCnt << std::endl;  //0 (=머지 할 수 없음) 으로 출력되면 게임오버. 
	*/

	if (tileValueCnt == MATRIX_SIZE * MATRIX_SIZE && isMergedCnt == 0) //타일이 꽉 찼고, 머지할 수 있는 요소도 없으면
	{
		return true; //게임 오버
	}
	else //아니면
	{
		return false; //계속 진행 
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
