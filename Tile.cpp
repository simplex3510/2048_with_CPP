#include "Tile.hpp"
#include "TextureManager.hpp"

#define TILE_SIZE 300

Tile::Tile() { }

Tile::Tile(const char* textureSheet)
{
	tileTexture = TextureManager::LoadTexture(textureSheet);

	value = 0;

	xPos = 410;
	yPos = 220;

	srcRect.h = TILE_SIZE;
	srcRect.w = TILE_SIZE;
	srcRect.x = 0;
	srcRect.y = 0;

	destRect.h = 100;
	destRect.w = 100;
	destRect.x = xPos;
	destRect.y = yPos;
}

Tile::~Tile()
{
}

void Tile::DrawTile()
{
	TextureManager::Draw(tileTexture, srcRect, destRect);
}

int Tile::getValue()
{
	return value;
}

void Tile::setValue(int value)
{
	this->value = value;
}
