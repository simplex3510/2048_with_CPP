#include "WindowManager.hpp"
#include "TextureManager.hpp"

#include "Background.hpp"
#include "TileMatrix.hpp"
#include "Text.hpp"

#include "GameLogic.hpp"

#define BACKGROUND_SIZE 450

using namespace std;

SDL_Renderer* WindowManager::renderer = nullptr;

GameBackground* gameBackground;
ScoreBackground* bestBackground;
ScoreBackground* scoreBackground;

TileMatrix* tileMatrix;

Text* scoreText;
Text* bestText;

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

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
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

	if (TTF_Init() == 0)
	{
		scoreText = new Text();
		bestText = new Text();
		if (scoreText != nullptr || bestText == nullptr)
		{
			cout << "Text Font Setting Complete" << endl;
		}
	}
	else    // 초기화 실패 시
	{
		isRunning = false;
		cout << "Initialize Failed" << endl;
		throw exception("Initialize Failed");
	}

	gameBackground = new GameBackground("Assets/GameBackground.png", 410, 220, 460, 460);
	bestBackground = new ScoreBackground("Assets/BestBackground.png", 400, 50, 230, 100);
	scoreBackground = new ScoreBackground("Assets/ScoreBackground.png", 650, 50, 230, 100);
	
	tileMatrix = new TileMatrix();
}

void WindowManager::HandleEvent()
{
	SDL_Event event;
	SDL_PollEvent(&event);

	if (event.type == SDL_QUIT)
	{
		isRunning = false;
	}
	else if (event.type == SDL_KEYUP)
	{

		switch (event.key.keysym.sym)
		{
		case SDLK_UP:
			cout << "KeyUP: Up" << endl;
			gamelogic::Rotate90(); gamelogic::Rotate90(); gamelogic::Rotate90();
			gamelogic::Sort();
			gamelogic::Merge();
			// done
			gamelogic::Sort();
			gamelogic::Rotate90();

			gamelogic::CreateNewTile();
			scoreText->Update();
			break;
		case SDLK_DOWN:
			cout << "KeyUP: Down" << endl;
			gamelogic::Rotate90();
			gamelogic::Sort();
			gamelogic::Merge();
			// done
			gamelogic::Sort();
			gamelogic::Rotate90(); gamelogic::Rotate90(); gamelogic::Rotate90();

			gamelogic::CreateNewTile();
			scoreText->Update();
			break;
		case SDLK_LEFT:
			cout << "KeyUP: Left" << endl;
			gamelogic::Sort();
			gamelogic::Merge();
			// done
			gamelogic::Sort();

			gamelogic::CreateNewTile();
			scoreText->Update();
			break;
		case SDLK_RIGHT:
			cout << "KeyUP: Right" << endl;
			gamelogic::Rotate90(); gamelogic::Rotate90();
			gamelogic::Sort();
			gamelogic::Merge();
			// done
			gamelogic::Sort();
			gamelogic::Rotate90(); gamelogic::Rotate90();

			gamelogic::CreateNewTile();
			scoreText->Update();
			break;
		default:
			break;
		}
	}
}

void WindowManager::Update()
{

}

void WindowManager::Render()
{
	SDL_RenderClear(renderer);
	
	gameBackground->Render();
	bestBackground->Render();
	scoreBackground->Render();

	tileMatrix->DrawTile();

	scoreText->Render();

	SDL_RenderPresent(renderer);
}

void WindowManager::Clear()
{
	//SDL_DestroyRenderer(renderer);	// 왠진 모르겠지만 에러 발생
	SDL_DestroyWindow(window);
	SDL_Quit();
	IMG_Quit();
	TTF_Quit();
	cout << "Destroy Window and Renderer" << endl;
}

bool WindowManager::Run()
{
	return isRunning;
}
