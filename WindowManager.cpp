#include "WindowManager.hpp"
#include "TextureManager.hpp"
#include "BestScoreManager.hpp"

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
RevertBox* revertBox;
EndScreen* endScreen;

TileMatrix* tileMatrix;

Text* tutorialTextL;
Text* tutorialTextR;
Text* scoreText;
Text* bestText;
Text* endText;

bool isTutorial = true;
bool gameEnd = false;
bool gameClear = false;

int mergedTile = -1;	// GameLogic::Merge에서 반환값을 받음. 머지 여부 및 2048 타일 생성 확인에 사용.



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
		bestText = new Text(450, 100, true);
		scoreText = new Text(750, 100, false);
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

	revertBox = new RevertBox("Assets/RevertBox.png", 565, 165, 150, 40);
	
	endScreen = new EndScreen("Assets/EndScreen.png");

	tileMatrix = new TileMatrix();
	
	//튜토리얼 텍스트 설정
	tutorialTextL = new Text("Use your arrow keys to move the tiles.\nTiles with the same number merge into one when they touch.\nAdd them up to \nreach 1!\n\nex) 2048 + 2048 = 1024..", false);
	tutorialTextR = new Text("BackSpace key : \nDelete Big Number Tile(More than 512)\n\nb key: \nRevert Rrevious Turn\n\ne key: \nGame Start", true);
	cout << endl << "Tutorial.. press to e key" << endl;

	
}

void WindowManager::HandleEvent()
{
	SDL_Event event;
	SDL_PollEvent(&event);

	int movedCnt = 0;	// 타일 이동 횟수와 머지 횟수 (합쳐질 때 다시 정렬할 필요가 없는 경우도 있어서 머지 횟수도 따로 더해줌)
	
	
	//튜토리얼 중일떄는 true, 끝나고 다음 단계 중부터는 false로 나타내기
	//e 키 누르면 텍스트 삭제 + bool 변수 false로 나타내서 여기 구문 실행 안되게 하기
	if (event.key.keysym.sym == SDLK_e && isTutorial == true) {
		
		isTutorial = false;
		delete tutorialTextL;
		delete tutorialTextR;
	}

	if (event.type == SDL_QUIT && isTutorial == false) //윈도우창 닫으면 SDL_QUIT 이벤트 발생
	{
		isRunning = false;
	}
	else if (event.type == SDL_KEYUP && isTutorial == false && gameEnd == false)
	{
		cout << "\nbefore " << movedCnt << endl;
		//임의의 키 눌렀을 시 승리/패배 이벤트 발생. 실제 게임에서 이벤트 발생시키는 코드는 update에 있음
		switch (event.key.keysym.sym)
		{
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

		// 512 이상 타일 제거
		case SDLK_BACKSPACE:
			gamelogic::Revert(false);	// 타일 상태 저장
			gamelogic::DeleteBigNumber();
			break;

		// B 누르면 이전 상태로
		case SDLK_b:
			gamelogic::Revert(true);	// 이전 상태로 돌리기
			break;

		// 뒤로 되돌리기
		case SDLK_SPACE:

			break;

		case SDLK_UP:
			cout << "KeyUP: Up" << endl;
			gamelogic::Revert(false);	// 타일 상태 저장
			gamelogic::Rotate90(); gamelogic::Rotate90(); gamelogic::Rotate90();
			movedCnt += gamelogic::Sort();	// merge 전 타일 한 쪽으로 몰기
			mergedTile = gamelogic::Merge();	// WindowManager::Update()에서 2048 타일 생성을 통한 승리 판정을 위해 따로 저장
			movedCnt += mergedTile;			// merge도 이동에 포함
			// done
			movedCnt += gamelogic::Sort();	// merge 후 빈 공간 채우기 위해서 한 번 더 sort
			gamelogic::Rotate90();

			if (movedCnt != -1)
				gamelogic::CreateNewTile();
			scoreText->Update();
			cout << "UP " << movedCnt << endl;
			break;

		case SDLK_DOWN:
			cout << "KeyUP: Down" << endl;
			gamelogic::Revert(false);	// 타일 상태 저장
			gamelogic::Rotate90();
			movedCnt += gamelogic::Sort();	// merge 전 타일 한 쪽으로 몰기
			mergedTile = gamelogic::Merge();	// WindowManager::Update()에서 2048 타일 생성을 통한 승리 판정을 위해 따로 저장
			movedCnt += mergedTile;			// merge도 이동에 포함
			// done
			movedCnt += gamelogic::Sort();	// merge 후 빈 공간 채우기 위해서 한 번 더 sort
			gamelogic::Rotate90(); gamelogic::Rotate90(); gamelogic::Rotate90();

			if (movedCnt != -1)
				gamelogic::CreateNewTile();
			scoreText->Update();
			cout << "DOWN " << movedCnt << endl;
			break;

		case SDLK_LEFT:
			cout << "KeyUP: Left" << endl;
			gamelogic::Revert(false);	// 타일 상태 저장
			movedCnt += gamelogic::Sort();	// merge 전 타일 한 쪽으로 몰기
			mergedTile = gamelogic::Merge();	// WindowManager::Update()에서 2048 타일 생성을 통한 승리 판정을 위해 따로 저장
			movedCnt += mergedTile;			// merge도 이동에 포함
			// done
			movedCnt += gamelogic::Sort();	// merge 후 빈 공간 채우기 위해서 한 번 더 sort

			if (movedCnt != -1)
				gamelogic::CreateNewTile();
			scoreText->Update();
			cout << "LEFT " << movedCnt << endl;
			break;

		case SDLK_RIGHT:
			cout << "KeyUP: Right" << endl;
			gamelogic::Revert(false);	// 타일 상태 저장
			gamelogic::Rotate90(); gamelogic::Rotate90();
			movedCnt += gamelogic::Sort();	// merge 전 타일 한 쪽으로 몰기
			mergedTile = gamelogic::Merge();	// WindowManager::Update()에서 2048 타일 생성을 통한 승리 판정을 위해 따로 저장
			movedCnt += mergedTile;			// merge도 이동에 포함
			// done
			movedCnt += gamelogic::Sort();	// merge 후 빈 공간 채우기 위해서 한 번 더 sort
			gamelogic::Rotate90(); gamelogic::Rotate90();

			if (movedCnt != -1)
				gamelogic::CreateNewTile();
			scoreText->Update();
			cout << "RIGHT " << movedCnt << endl;
			break;

		default:
			break;
		}
		cout << "after " << movedCnt << endl;
	}
}

void WindowManager::Update()
{
	// 승패 판정
	if (mergedTile == 0 && gameEnd == false) //게임 클리어
	{
		BestScore(totalScore);
		cout << "Game Clear" << endl;
		gameEnd = true;
		gameClear = true;
	}
	else if(gamelogic::CheckGameOver() && gameEnd == false) //게임 오버
	{
		BestScore(totalScore);
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
	revertBox->Render();

	tileMatrix->DrawTile();

	bestText->Render();
	scoreText->Render();

	if (isTutorial == true) { 
		tutorialTextL->Render();
		tutorialTextR->Render();
	}

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
