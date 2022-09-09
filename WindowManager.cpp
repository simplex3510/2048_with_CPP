#include "TextureManager.hpp"
#include "WindowManager.hpp"

#define BACKGROUND_SIZE 450

using namespace std;

SDL_Texture* backgroundTexture;
SDL_Rect srcRect, destRect;

WindowManager::WindowManager()
{

}

WindowManager::~WindowManager()
{

}

void WindowManager::Initialize(const char* title, int xPos, int yPos, int width, int height, bool isFullScreen)
{
	int flags = 0;

	if (isFullScreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == NULL)
	{
		cout << "Systems Initialize" << endl;

		window = SDL_CreateWindow(title, xPos, yPos, width, height, flags);
		if (window != nullptr)
		{
			cout << "Window Created" << endl;
		}

		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer != nullptr)
		{
			SDL_SetRenderDrawColor(renderer, 250, 248, 239, 255);
			cout << "Renderer Created" << endl;
		}

		isRunning = true;
	}
	else    // 초기화 실패 시
	{
		isRunning = false;
		cout << "Initialize Failed" << endl;
		throw exception("Initialize Failed");
	}

	backgroundTexture = TextureManager::LoadTexture("Assets/Background.png", renderer);

	destRect.w = BACKGROUND_SIZE;
	destRect.h = BACKGROUND_SIZE;
}

void WindowManager::HandleEvent()
{
	SDL_Event event;
	SDL_PollEvent(&event);

	switch (event.type)
	{
	case SDL_QUIT:
		isRunning = false;
		break;
	default:
		break;
	}
}

void WindowManager::Update()
{

}

void WindowManager::Render()
{
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, backgroundTexture, NULL, &destRect);
	SDL_RenderPresent(renderer);

}

void WindowManager::Clear()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	cout << "Destroy Window and Renderer" << endl;
}

bool WindowManager::Run()
{
	return isRunning;
}
