#pragma once

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "SingletonBase.hpp"


class WindowManager : public SingletonBase<WindowManager>
{
public:
	static SDL_Renderer* renderer;
	
	WindowManager();
	~WindowManager();

	void Initialize(const char* title, int xPos, int yPos, int width, int height, bool fullScreen);

	void HandleEvent();
	void Update();
	void Render();
	void Clear();

	bool Run();

private:
	bool isRunning;
	SDL_Window* window;
};