//#include <ctime>
//#include <conio.h>
//
//#include "Renderer.h"
//#include "ScreenManager.h"
//
//#define UP 72
//#define DOWN 80
//#define LEFT 75
//#define RIGHT 77
//
//ScreenManager* gpScreenManager = ScreenManager::getInstance();
//Renderer* gpRenderer = Renderer::getInstance();
//
//void InitializeApplication();
//void Update();
//void Render();
//void Release();
//int getKeyEvent();
//void KeyProcess(int key);
//
//int main()
//{
//	clock_t curTime, oldTime;
//
//	InitializeApplication();
//
//	int inputKeyValue = 0;
//	while (true)
//	{
//		oldTime = clock();
//
//		inputKeyValue = getKeyEvent();
//		if (inputKeyValue == 'q')
//			break;
//
//		KeyProcess(inputKeyValue);
//
//		Update();		//데이터 갱신        
//		Render();		//화면 출력
//
//		while (true)	//대기 상태 진입
//		{
//			curTime = clock();
//			if (33 < curTime - oldTime)		// 약 30fps 유지
//				break;
//		}
//	}
//
//	Release();//해제
//
//	return 0;
//}
//
//void InitializeApplication()
//{
//	gpScreenManager->InitScreen();
//	gpRenderer->RenderingTitle();
//	gpRenderer->RenderingFrame();
//}
//
//void Update()
//{
//}
//
//void Render()
//{
//	gpScreenManager->ClearScreen();
//	//DrawFPS(&fpsData);
//	gpRenderer->RenderingTitle();
//
//	gpScreenManager->FlipScreen();
//}
//
//void Release()
//{
//	//DestoyFPSData(&fpsData);
//	gpScreenManager->ReleaseScreen();
//
//	delete gpScreenManager;
//	delete gpRenderer;
//}
//
//int getKeyEvent()
//{
//	if (_kbhit())
//		return _getch();
//
//	return -1;
//}
//
//void KeyProcess(int key)
//{
//	switch (key)
//	{
//	case 'i':
//		break;
//	case'j':
//		break;
//	}
//}
