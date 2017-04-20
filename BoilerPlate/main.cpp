#if _MSC_VER && _DEBUG
	#define _CRTDBG_MAP_ALLOC
	#include <crtdbg.h>
#endif

// C++ STL
#include <cassert>
#include <iostream>

// 
#include "App.hpp"
#include "Game.h"
#include "AppSettings.h"
#include "DirectoryUtils.h"

const int WIDTH = 1136;
const int HEIGHT = 640;
const int FPS = 60;
const int DELAY_TIME = 1000.0f / FPS;

using namespace Asteroids::Utilities;

int main(int argc, char* argv[])
{
#if _MSC_VER && _DEBUG
	// https://msdn.microsoft.com/en-us/library/x98tx3cf.aspx
	// This will help you detect leaks when using Visual C++
	// Uncomment this line to start getting reports!
	assert(_CrtCheckMemory());
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	Uint32 frameStart, frameTime;

	if (Game::Instance()->Init("Asteroids", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT))
	{ 
		while (Game::Instance()->Running()) 
		{
			frameStart = SDL_GetTicks();

			Game::Instance()->HandleEvents();
			Game::Instance()->Update();
			Game::Instance()->Render();

			frameTime = SDL_GetTicks() - frameStart;

			if (frameTime < DELAY_TIME) 
			{
				SDL_Delay((int)(DELAY_TIME - frameTime));
			}

			if (AppSettings::Instance()->IsGameOver())
			{
				AppSettings::Instance()->SaveScoreData();
				Game::Instance()->Quit();
				cout << "YOUR SCORE IS " <<AppSettings::Instance()->GetScores()<<endl;
			    std::cout << "GAME OVER!!" << std::endl;
			}

		}
	}

	Game::Instance()->Destroy();

	
	system("pause");
	return 0;
}