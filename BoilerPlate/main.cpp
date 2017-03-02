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

const int WIDTH = 1136;
const int HEIGHT = 640;



int main(int argc, char* argv[])
{
#if _MSC_VER && _DEBUG
	// https://msdn.microsoft.com/en-us/library/x98tx3cf.aspx
	// This will help you detect leaks when using Visual C++
	// Uncomment this line to start getting reports!
	assert(_CrtCheckMemory());
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	Uint32 flags = SDL_WINDOW_OPENGL |
		SDL_WINDOW_SHOWN |
		SDL_WINDOW_RESIZABLE;
	
	if (Game::Instance()->init("Asteroids", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, flags))
	{ 
		while (Game::Instance()->running()) 
		{

			Game::Instance()->handleEvents();
			Game::Instance()->update();
			Game::Instance()->render();
		}
	}

	Game::Instance()->clean();
	return 0;
}