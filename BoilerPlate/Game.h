#pragma once
#ifndef _Game_
#define _Game_
#include "SDL.h"
#include "iostream"
#include "vector"
#include "Vector2D.h"
#include "GameObject.h"
#include "Ship.h"
using namespace Engine::Math;
class Game
{
public:
	
	std::string getWindowTitle();
	int getWindowXPos();
	int getWindowYPos();
	int getWindowWidth();
	int getWindowHeight();
	void setWindowTitle(std::string gameTitle);
	void setWindowXPos(int xpos);
	void setWindowYPos(int ypos);
	void setWindowWidth(int width);
	void setWindowHeight(int height);
	//simply set the running variable to true
	bool init(const char* title, int xpos, int ypos, int width, int height);
	void render();
	void update();
	void handleEvents();
	void clean();
	static Game* Instance();
	bool running();
	void quit();
private:
	Game();
	~Game();
	static Game* m_instance;
	int m_windowWidth;
	int m_windowHeight;
	int m_windowXPos;
	int m_windowYPos;
	bool m_running;
	std::string m_windowTitle;
	SDL_Window* m_Window;
	SDL_GLContext m_context;
	bool initSDL();
	bool initGlew();
	void SetupViewPort();
	
};
#endif