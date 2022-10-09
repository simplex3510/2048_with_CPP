#include "WindowManager.hpp"
#include "TextureManager.hpp"

#include "Background.hpp"
#include "EndScreen.hpp"
#include "TileMatrix.hpp"
#include "Text.hpp"

#include "GameLogic.hpp"

#define BACKGROUND_SIZE 450

using namespace std;

SDL_Renderer* WindowManager::renderer = nullptr;

GameBackground* gameBackground;
ScoreBackground* bestBackground;
ScoreBackground* scoreBackground;
EndScreen* endScreen;

TileMatrix* tileMatrix;

Text* scoreText;
Text* bestText;
Text* endText;

bool gameEnd = false;
bool gameClear = false;

int mergedTile = 0;	// GameLogic::Merge에서 반환값을 받음. 머지 여부 및 2048 타일 생성 확인에 사용.

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
		bestText = new Text(506, 100);
		scoreText = new Text(750, 100);
		if (scoreText != nullptr && bestText != nullptr)
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
	
	endScreen = new EndScreen("Assets/EndScreen.png");

	tileMatrix = new TileMatrix();
}

void WindowManager::HandleEvent()
{
	SDL_Event event;
	SDL_PollEvent(&event);

	int movedCnt = 0;	// 타일 이동 횟수와 머지 횟수 (합쳐질 때 다시 정렬할 필요가 없는 경우도 있어서 머지 횟수도 따로 더해줌)

	if (event.type == SDL_QUIT) //윈도우창 닫으면 SDL_QUIT 이벤트 발생
	{
		isRunning = false;
	}
	else if (event.type == SDL_KEYUP && gameEnd == false)
	{
		switch (event.key.keysym.sym)
		{//임의의 키 눌렀을 시 승리/패배 이벤트 발생. 실제 게임에서 이벤트 발생시키는 코드는 update에 있음
		case SDLK_1: //1키 입력시 게임 클리어
			cout << "Game Clear" << endl;
			gameEnd = true;
			gameClear = true;
			break;
		case SDLK_2: //2키 입력시 게임 오버 
			cout << "Game Over" << endl;
			gameEnd = true;
			gameClear = false;
			break;

		case SDLK_UP:
			cout << "KeyUP: Up" << endl;
			gamelogic::Rotate90(); gamelogic::Rotate90(); gamelogic::Rotate90();
			movedCnt += gamelogic::Sort();	// merge 전 타일 한 쪽으로 몰기
			mergedTile = gamelogic::Merge();	// WindowManager::Update()에서 2048 타일 생성을 통한 승리 판정을 위해 따로 저장
			movedCnt += mergedTile;			// merge도 이동에 포함
			// done
			movedCnt += gamelogic::Sort();	// merge 후 빈 공간 채우기 위해서 한 번 더 sort
			gamelogic::Rotate90();

			if (movedCnt)
				gamelogic::CreateNewTile();
			scoreText->Update();
			break;
		case SDLK_DOWN:
			cout << "KeyUP: Down" << endl;
			gamelogic::Rotate90();
			movedCnt += gamelogic::Sort();	// merge 전 타일 한 쪽으로 몰기
			mergedTile = gamelogic::Merge();	// WindowManager::Update()에서 2048 타일 생성을 통한 승리 판정을 위해 따로 저장
			movedCnt += mergedTile;			// merge도 이동에 포함
			// done
			movedCnt += gamelogic::Sort();	// merge 후 빈 공간 채우기 위해서 한 번 더 sort
			gamelogic::Rotate90(); gamelogic::Rotate90(); gamelogic::Rotate90();

			if (movedCnt)
				gamelogic::CreateNewTile();
			scoreText->Update();
			break;
		case SDLK_LEFT:
			cout << "KeyUP: Left" << endl;
			movedCnt += gamelogic::Sort();	// merge 전 타일 한 쪽으로 몰기
			mergedTile = gamelogic::Merge();	// WindowManager::Update()에서 2048 타일 생성을 통한 승리 판정을 위해 따로 저장
			movedCnt += mergedTile;			// merge도 이동에 포함
			// done
			movedCnt += gamelogic::Sort();	// merge 후 빈 공간 채우기 위해서 한 번 더 sort

			if (movedCnt)
				gamelogic::CreateNewTile();
			scoreText->Update();
			break;
		case SDLK_RIGHT:
			cout << "KeyUP: Right" << endl;
			gamelogic::Rotate90(); gamelogic::Rotate90();
			movedCnt += gamelogic::Sort();	// merge 전 타일 한 쪽으로 몰기
			mergedTile = gamelogic::Merge();	// WindowManager::Update()에서 2048 타일 생성을 통한 승리 판정을 위해 따로 저장
			movedCnt += mergedTile;			// merge도 이동에 포함
			// done
			movedCnt += gamelogic::Sort();	// merge 후 빈 공간 채우기 위해서 한 번 더 sort
			gamelogic::Rotate90(); gamelogic::Rotate90();

			if (movedCnt)
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
	// 승패 판정
	if (mergedTile == 2048 && gameEnd == false) //게임 클리어
	{
		cout << "Game Clear" << endl;
		gameEnd = true;
		gameClear = true;
	}
	else if(gamelogic::CheckGameOver() && gameEnd == false) //게임 오버
	{
		cout << "Game Over" << endl;
		gameEnd = true; 
		gameClear = false;
	}

}

void WindowManager::Render()
{
	SDL_RenderClear(renderer);
	
	gameBackground->Render();
	bestBackground->Render();
	scoreBackground->Render();

	tileMatrix->DrawTile();

	bestText->Render();
	scoreText->Render();

	if (gameEnd == true)
	{
		endScreen->Render();

		if (gameClear == true)
		{
			endText = new Text("Game Clear");
		}
		else
		{
			endText = new Text("Game Over");
		}
		
		endText->Render();
	}

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
