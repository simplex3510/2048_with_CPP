#include <ctime>
#include <conio.h>

#include "Renderer.h"
#include "ScreenManager.h"

#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77

void gameInit();

int main()
{
	clock_t curTime, oldTime;

	gameInit();

	//while (true)
	//{
	//	oldTime = clock();

	//	Update();		//데이터 갱신        
	//	Render();		//화면 출력

	//	while (true)	//대기 상태 진입
	//	{
	//		curTime = clock();
	//		if (33 < curTime - oldTime)		// 60fps 유지
	//			break;
	//	}
	//}
	//
	//	Release();//해제

		return 0;
	}

	void gameInit()
	{
		system("mode con cols=100 lines=50");
		system("title Test2048");
		SetConsoleTitleW(L"Test2048");

		titleRenderer();
		ScreenManager::getInstance();
	}