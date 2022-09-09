#pragma once

#include <SDL_image.h>

#include "SingletonBase.hpp"

class TextureManager : public SingletonBase<TextureManager>
{
public:
	static SDL_Texture* LoadTexture(const char* fileName, SDL_Renderer* renderer);

	TextureManager();
	~TextureManager();

private:

};
