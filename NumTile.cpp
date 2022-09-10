#include "NumTile.hpp"
#include "TextureManager.hpp"

NumTile::NumTile() : Tile()
{
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

NumTile::~NumTile()
{
}
