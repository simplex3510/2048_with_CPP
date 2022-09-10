#pragma once

#include "SingletonBase.hpp"
#include "WindowManager.hpp"

class TextureManager : public SingletonBase<TextureManager>
{
public:
	static SDL_Texture* LoadTexture(const char* fileName);

	TextureManager();
	~TextureManager();

private:

};
