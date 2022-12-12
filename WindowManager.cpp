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

int mergedTile = -1;	// GameLogic::Merge���� ��ȯ���� ����. ���� ���� �� 2048 Ÿ�� ���� Ȯ�ο� ���.



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
	else    // �ʱ�ȭ ���� ��
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
	else    // �ʱ�ȭ ���� ��
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
	
	//Ʃ�丮�� �ؽ�Ʈ ����
	tutorialTextL = new Text("Use your arrow keys to move the tiles.\nTiles with the same number merge into one when they touch.\nAdd them up to \nreach 1!\n\nex) 2048 + 2048 = 1024..", false);
	tutorialTextR = new Text("BackSpace key : \nDelete Big Number Tile(More than 512)\n\nb key: \nRevert Rrevious Turn\n\ne key: \nGame Start", true);
	cout << endl << "Tutorial.. press to e key" << endl;

	
}

void WindowManager::HandleEvent()
{
	SDL_Event event;
	SDL_PollEvent(&event);

	int movedCnt = 0;	// Ÿ�� �̵� Ƚ���� ���� Ƚ�� (������ �� �ٽ� ������ �ʿ䰡 ���� ��쵵 �־ ���� Ƚ���� ���� ������)
	
	
	//Ʃ�丮�� ���ϋ��� true, ������ ���� �ܰ� �ߺ��ʹ� false�� ��Ÿ����
	//e Ű ������ �ؽ�Ʈ ���� + bool ���� false�� ��Ÿ���� ���� ���� ���� �ȵǰ� �ϱ�
	if (event.key.keysym.sym == SDLK_e && isTutorial == true) {
		
		isTutorial = false;
		delete tutorialTextL;
		delete tutorialTextR;
	}

	if (event.type == SDL_QUIT && isTutorial == false) //������â ������ SDL_QUIT �̺�Ʈ �߻�
	{
		isRunning = false;
	}
	else if (event.type == SDL_KEYUP && isTutorial == false && gameEnd == false)
	{
		cout << "\nbefore " << movedCnt << endl;
		//������ Ű ������ �� �¸�/�й� �̺�Ʈ �߻�. ���� ���ӿ��� �̺�Ʈ �߻���Ű�� �ڵ�� update�� ����
		switch (event.key.keysym.sym)
		{
		case SDLK_1: //1Ű �Է½� ���� Ŭ����
			cout << "Game Clear" << endl;
			gameEnd = true;
			gameClear = true;
			break;

		case SDLK_2: //2Ű �Է½� ���� ���� 
			cout << "Game Over" << endl;
			gameEnd = true;
			gameClear = false;
			break;

		// 512 �̻� Ÿ�� ����
		case SDLK_BACKSPACE:
			gamelogic::Revert(false);	// Ÿ�� ���� ����
			gamelogic::DeleteBigNumber();
			break;

		// B ������ ���� ���·�
		case SDLK_b:
			gamelogic::Revert(true);	// ���� ���·� ������
			break;

		// �ڷ� �ǵ�����
		case SDLK_SPACE:

			break;

		case SDLK_UP:
			cout << "KeyUP: Up" << endl;
			gamelogic::Revert(false);	// Ÿ�� ���� ����
			gamelogic::Rotate90(); gamelogic::Rotate90(); gamelogic::Rotate90();
			movedCnt += gamelogic::Sort();	// merge �� Ÿ�� �� ������ ����
			mergedTile = gamelogic::Merge();	// WindowManager::Update()���� 2048 Ÿ�� ������ ���� �¸� ������ ���� ���� ����
			movedCnt += mergedTile;			// merge�� �̵��� ����
			// done
			movedCnt += gamelogic::Sort();	// merge �� �� ���� ä��� ���ؼ� �� �� �� sort
			gamelogic::Rotate90();

			if (movedCnt != -1)
				gamelogic::CreateNewTile();
			scoreText->Update();
			cout << "UP " << movedCnt << endl;
			break;

		case SDLK_DOWN:
			cout << "KeyUP: Down" << endl;
			gamelogic::Revert(false);	// Ÿ�� ���� ����
			gamelogic::Rotate90();
			movedCnt += gamelogic::Sort();	// merge �� Ÿ�� �� ������ ����
			mergedTile = gamelogic::Merge();	// WindowManager::Update()���� 2048 Ÿ�� ������ ���� �¸� ������ ���� ���� ����
			movedCnt += mergedTile;			// merge�� �̵��� ����
			// done
			movedCnt += gamelogic::Sort();	// merge �� �� ���� ä��� ���ؼ� �� �� �� sort
			gamelogic::Rotate90(); gamelogic::Rotate90(); gamelogic::Rotate90();

			if (movedCnt != -1)
				gamelogic::CreateNewTile();
			scoreText->Update();
			cout << "DOWN " << movedCnt << endl;
			break;

		case SDLK_LEFT:
			cout << "KeyUP: Left" << endl;
			gamelogic::Revert(false);	// Ÿ�� ���� ����
			movedCnt += gamelogic::Sort();	// merge �� Ÿ�� �� ������ ����
			mergedTile = gamelogic::Merge();	// WindowManager::Update()���� 2048 Ÿ�� ������ ���� �¸� ������ ���� ���� ����
			movedCnt += mergedTile;			// merge�� �̵��� ����
			// done
			movedCnt += gamelogic::Sort();	// merge �� �� ���� ä��� ���ؼ� �� �� �� sort

			if (movedCnt != -1)
				gamelogic::CreateNewTile();
			scoreText->Update();
			cout << "LEFT " << movedCnt << endl;
			break;

		case SDLK_RIGHT:
			cout << "KeyUP: Right" << endl;
			gamelogic::Revert(false);	// Ÿ�� ���� ����
			gamelogic::Rotate90(); gamelogic::Rotate90();
			movedCnt += gamelogic::Sort();	// merge �� Ÿ�� �� ������ ����
			mergedTile = gamelogic::Merge();	// WindowManager::Update()���� 2048 Ÿ�� ������ ���� �¸� ������ ���� ���� ����
			movedCnt += mergedTile;			// merge�� �̵��� ����
			// done
			movedCnt += gamelogic::Sort();	// merge �� �� ���� ä��� ���ؼ� �� �� �� sort
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
	// ���� ����
	if (mergedTile == 0 && gameEnd == false) //���� Ŭ����
	{
		BestScore(totalScore);
		cout << "Game Clear" << endl;
		gameEnd = true;
		gameClear = true;
	}
	else if(gamelogic::CheckGameOver() && gameEnd == false) //���� ����
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
	//SDL_DestroyRenderer(renderer);	// ���� �𸣰����� ���� �߻�
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
