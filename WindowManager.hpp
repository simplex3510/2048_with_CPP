#pragma once

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

#include "SingletonBase.hpp"


class WindowManager : public SingletonBase<WindowManager>
{
public:
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
	SDL_Renderer* renderer;
};