#include "BaseTile.hpp"
#include "TextureManager.hpp"

BaseTile::BaseTile(const char* textureSheet) : Tile(textureSheet)
{
	destRect.x = xPos + 10;
	destRect.y = yPos + 10;

	LoadTile();
}

BaseTile::~BaseTile()
{
	delete[] tileMap;
}

void BaseTile::LoadTile()
{
	for (int row = 0; row < MAP_SIZE; row++)
	{
		for (int column = 0; column < MAP_SIZE; column++)
		{
			tileMap[row][column] = new Tile("Assets/TileBase.png");
		}
	}
}

void BaseTile::DrawTile()
{
	for (int row = 0; row < MAP_SIZE; row++)
	{
		for (int column = 0; column < MAP_SIZE; column++)
		{
			tileMap[row][column]->destRect.x = 410 + 15 + 110 * column;
			tileMap[row][column]->destRect.y = 220 + 15 + 110 * row;

			TextureManager::Draw(tileMap[row][column]->tileTexture, tileMap[row][column]->srcRect, tileMap[row][column]->destRect);
		}
	}
}