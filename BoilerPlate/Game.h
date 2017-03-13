#pragma once
#ifndef _Game_
#define _Game_
#include "SDL.h"
#include "iostream"
#include "vector"
#include "Vector2D.h"
#include "ShipPlayer.h"
#include "Asteroid.h"

using namespace Engine::Math;
class Game
{
public:
	~Game();
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
	static Game* m_instance;
	int m_windowWidth;
	int m_windowHeight;
	int m_windowXPos;
	int m_windowYPos;
	bool m_running;
	int m_lastFrameTime;
	std::string m_windowTitle;
	SDL_Window* m_Window;
	SDL_GLContext m_context;
	ShipPlayer* m_player;
	vector<OpenglGameObject*> m_gameObjects;
	bool initSDL();
	bool initGlew();
	void SetupViewPort();
	void CreatePlayers();
	void CreateAsteroids(int amount, Asteroid::AsteroidSize::Size size, Vector2D pos);
	void CreateDebris(Asteroid::AsteroidSize::Size size, Vector2D position);
	void CheckCollision(OpenglGameObject* object, int index);
	
	
};
#endif