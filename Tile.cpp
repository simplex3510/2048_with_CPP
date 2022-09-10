#include "Tile.hpp"
#include "TextureManager.hpp"

#define TILE_SIZE 300

Tile::Tile()
{
	LoadTile();

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

void Tile::LoadTile()
{
	tile0 = TextureManager::LoadTexture("Assets/Tile0.png");
	tile2 = TextureManager::LoadTexture("Assets/Tile2.png");
	tile4 = TextureManager::LoadTexture("Assets/Tile4.png");
	tile8 = TextureManager::LoadTexture("Assets/Tile8.png");
	tile16 = TextureManager::LoadTexture("Assets/Tile16.png");
	tile32 = TextureManager::LoadTexture("Assets/Tile32.png");
	tile64 = TextureManager::LoadTexture("Assets/Tile64.png");
	tile128 = TextureManager::LoadTexture("Assets/Tile128.png");
	tile256 = TextureManager::LoadTexture("Assets/Tile256.png");
	tile512 = TextureManager::LoadTexture("Assets/Tile512.png");
	tile1024 = TextureManager::LoadTexture("Assets/Tile1024.png");
	tile2048 = TextureManager::LoadTexture("Assets/Tile2048.png");
}

void Tile::DrawTile(int value)
{
	switch ((eTileValue)value)
	{
	case eTileValue::Tile0:
		TextureManager::Draw(tile0, srcRect, destRect);
		break;
	case eTileValue::Tile2:
		TextureManager::Draw(tile2, srcRect, destRect);
		break;
	case eTileValue::Tile4:
		TextureManager::Draw(tile4, srcRect, destRect);
		break;
	case eTileValue::Tile8:
		TextureManager::Draw(tile8, srcRect, destRect);
		break;
	case eTileValue::Tile16:
		TextureManager::Draw(tile16, srcRect, destRect);
		break;
	case eTileValue::Tile32:
		TextureManager::Draw(tile32, srcRect, destRect);
		break;
	case eTileValue::Tile64:
		TextureManager::Draw(tile64, srcRect, destRect);
		break;
	case eTileValue::Tile128:
		TextureManager::Draw(tile128, srcRect, destRect);
		break;
	case eTileValue::Tile256:
		TextureManager::Draw(tile256, srcRect, destRect);
		break;
	case eTileValue::Tile512:
		TextureManager::Draw(tile512, srcRect, destRect);
		break;
	case eTileValue::Tile1024:
		TextureManager::Draw(tile1024, srcRect, destRect);
		break;
	case eTileValue::Tile2048:
		TextureManager::Draw(tile2048, srcRect, destRect);
		break;
	default:
		break;
	}
}