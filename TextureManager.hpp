#pragma once

#include "SingletonBase.hpp"
#include "WindowManager.hpp"

class TextureManager : public SingletonBase<TextureManager>
{
public:
	static SDL_Texture* LoadTexture(const char* fileName);
	static void Draw(SDL_Texture* texture, SDL_Rect srcRect, SDL_Rect destRect);

	TextureManager();
	~TextureManager();

private:

};
