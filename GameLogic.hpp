#pragma once

#include <iostream>
#include <cstdlib>
#include <ctime>

#include "ETileValue.hpp"

#define MATRIX_SIZE 4

extern int totalScore;
extern eTileValue tileValue[MATRIX_SIZE][MATRIX_SIZE];

extern int tileValueCnt; //현재 몇개의 타일에 값이 있는지(=타일이 가득 찼는지) 확인. 게임오버 여부 체크에 사용.
extern int isMergedCnt; //머지 할 수 있는 타일이 있는지 여부 확인. 게임오버 여부 체크에 사용.

namespace gamelogic
{
	void Initialize();
	void CreateNewTile();

	void Rotate90();
	int Sort();
	int Merge();

	void PrintTileValueMatrix();

	bool CheckGameOver(); 

	void DeleteBigNumber();
}