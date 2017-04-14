#pragma once
#ifndef _Game_
#define _Game_
#include "SDL.h"
#include <iostream>
#include <vector>
#include "Vector2D.h"
#include "ShipPlayer.h"
#include "Asteroid.h"
#include "Bullet.h"
using namespace Engine::Math;
class Game
{
public:
	~Game();
	static Game* Instance();
	std::string getWindowTitle();
	int GetWindowXPos();
	int GetWindowYPos();
	int GetWindowWidth();
	int GetWindowHeight();
	void SetWindowTitle(std::string gameTitle);
	void SetWindowXPos(int xpos);
	void SetWindowYPos(int ypos);
	void SetWindowWidth(int width);
	void SetWindowHeight(int height);
	//simply set the running variable to true
	bool Init(const char* title, int xpos, int ypos, int width, int height);
	void Render();
	void Update();
	void HandleEvents();
	void Clean();
	bool Running();
	void Quit();
	void AddChild(OpenglGameObject* object);
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
	SDL_Window* m_window;
	SDL_GLContext m_context; 
	ShipPlayer* m_player;
	vector<OpenglGameObject*> m_gameObjects;
	vector<Bullet*>m_bullets;
	bool InitSDL();
	bool InitGlew();
	void SetupViewPort();
	void CreatePlayers();
	void CreateAsteroids(int amount, Asteroid::AsteroidSize::Size size, Vector2D pos);
	void CreateDebris(Asteroid::AsteroidSize::Size size, Vector2D position);
	void ScoreLogic(OpenglGameObject* object);
	void PlayerCollision();
	void BulletCollision();
	
};
#endif