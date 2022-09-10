#pragma once

#include "GameObject.hpp"

#define GAME_WIDTH   1418
#define GAME_HEIGHT  1418
#define SCORE_WIDTH  756
#define SCORE_HEIGHT 400

class Background : public GameObject
{
public:
	Background(const char* textureSheet, int xPos, int yPos, int width, int height);
	~Background();

private:

};

class GameBackground : public Background
{
public:
	GameBackground(const char* textureSheet, int xPos, int yPos, int width, int height) : Background(textureSheet, xPos, yPos, width, height)
	{
		srcRect.h = GAME_HEIGHT;
		srcRect.w = GAME_WIDTH;
		srcRect.x = 0;
		srcRect.y = 0;

		destRect.h = height;
		destRect.w = width;
		destRect.x = xPos;
		destRect.y = yPos;
	}
	~GameBackground();

private:

};

class ScoreBackground : public Background
{
public:
	ScoreBackground(const char* textureSheet, int xPos, int yPos, int width, int height) : Background(textureSheet, xPos, yPos, width, height)
	{
		srcRect.h = SCORE_HEIGHT;
		srcRect.w = SCORE_WIDTH;
		srcRect.x = 0;
		srcRect.y = 0;

		destRect.h = height;
		destRect.w = width;
		destRect.x = xPos;
		destRect.y = yPos;
	}
	~ScoreBackground();

private:

};