#pragma once

#include "Tile.hpp"

class BaseTile : public Tile
{
public:
	BaseTile(const char* textureSheet);
	~BaseTile();

	void LoadTile();
	void DrawTile() override;

private:
	Tile* tileMap[MAP_SIZE][MAP_SIZE];
};

