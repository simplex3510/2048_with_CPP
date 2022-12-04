#pragma once

#include <iostream>
#include <cstdlib>
#include <ctime>

#include "ETileValue.hpp"

#define MATRIX_SIZE 4

extern int totalScore;
extern eTileValue tileValue[MATRIX_SIZE][MATRIX_SIZE];

extern int tileValueCnt; //���� ��� Ÿ�Ͽ� ���� �ִ���(=Ÿ���� ���� á����) Ȯ��. ���ӿ��� ���� üũ�� ���.
extern int isMergedCnt; //���� �� �� �ִ� Ÿ���� �ִ��� ���� Ȯ��. ���ӿ��� ���� üũ�� ���.

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