#include "GameObject.hpp"
#include "TextureManager.hpp"

GameObject::GameObject(const char* textureSheet, int x, int y)
{
	objectTexture = TextureManager::LoadTexture(textureSheet);

	xPos = x;
	yPos = y;
}

GameObject::~GameObject()
{
}

void GameObject::Update()
{

}

void GameObject::Render()
{
	SDL_RenderCopy(WindowManager::renderer, objectTexture, &srcRect, &destRect);
}