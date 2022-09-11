#include "WindowManager.hpp"

#define WINDOW_WIDTH  1280
#define WINDOW_HEIGHT 720

#define FPS 30
#define FRAME_DELAY 1000 / FPS

static WindowManager* windowManager = WindowManager::getInstance();

int main(int argc, char* argv[])
{
	windowManager->Initialize("2048", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, false);

	Uint32 frameStart;
	int frameTime;

	while (windowManager->Run())
	{
		frameStart = SDL_GetTicks();

		windowManager->HandleEvent();
		windowManager->Update();
		windowManager->Render();
	
		frameTime = SDL_GetTicks() - frameStart;

		if (FRAME_DELAY < frameTime)
		{
			SDL_Delay(FRAME_DELAY);
		}
	}

	windowManager->Clear();

	return 0;
}