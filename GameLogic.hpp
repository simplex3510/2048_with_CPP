#pragma once

#include <iostream>
#include <cstdlib>
#include <ctime>

#include "ETileValue.hpp"

#define MATRIX_SIZE 4

extern int totalScore;
extern eTileValue tileValue[MATRIX_SIZE][MATRIX_SIZE];

namespace gamelogic
{
	void Initialize();
	void CreateTileValue();

	void Rotate90();
	void Sort();
	void Merge();
}