
#include "Game.h"
#include <string>
#include <algorithm>

//OPENGL 
#include "glew.h"
#include "SDL_opengl.h"


#include "Entity.h"
#include "AppSettings.h"

using namespace Engine::Math;
using namespace Asteroids::Entities;
using namespace Asteroids::Utilities;

const float DESIRED_FRAME_RATE = 60.0f;
const float DESIRED_FRAME_TIME = 1.0f / DESIRED_FRAME_RATE;
Game* Game::m_instance = 0;


#pragma region CTOR AND DTOR
Game::Game()
{
	
}

Game::~Game()
{
	Clean();
	delete m_instance;
	m_instance = nullptr;
}
#pragma endregion

#pragma region GETTERS AND SETTERS
std::string Game::getWindowTitle()
{
	return m_windowTitle;
}

int Game::GetWindowXPos()
{
	return m_windowXPos;
}

int Game::GetWindowYPos()
{
	return m_windowYPos;
}

int Game::GetWindowWidth()
{
	return m_windowWidth;
}

int Game::GetWindowHeight()
{
	return m_windowHeight;
}

void Game::SetWindowTitle(std::string gameTitle)
{
	m_windowTitle = gameTitle;
}

void Game::SetWindowXPos(int xpos)
{
	m_windowXPos = xpos;
}

void Game::SetWindowYPos(int ypos)
{
	m_windowYPos = ypos;
}

void Game::SetWindowWidth(int width)
{
	m_windowWidth = width;
}

void Game::SetWindowHeight(int height)
{
	m_windowHeight = height;
}

Game * Game::Instance()
{
	if (Game::m_instance == 0)
	{
		Game::m_instance = new Game();
		return Game::m_instance;
	}
	return Game::m_instance;
}
#pragma endregion

#pragma region PUBLIC METHODS
bool Game::Init(const char * title, int xpos, int ypos, int width, int height)
{

	SetWindowTitle(title);
	SetWindowXPos(xpos);
	SetWindowYPos(ypos);
	SetWindowWidth(width);
	SetWindowHeight(height);

	// Init the external dependencies
	//
	bool success = InitSDL() && InitGlew();
	if (!success)
	{
		m_running = false;
		return false;
	}

	// Setup the viewport
	//
	SetupViewPort();



	m_running = true;// everything inited successfully 
					  //star the main loop

    
	//Creating Players
	CreatePlayers();

	//Creating Asteroids
	CreateAsteroids(1 , Asteroid::AsteroidSize::BIG,Vector2D::Origin);

	//Creating the Enemy Ship
	 this->m_enemy = new ShipEnemy();
	this->m_gameObjects.push_back(m_enemy);


	//Setting amound of rounds
	AppSettings::Instance()->SetModelLiveIcon(m_player->GetPoints());
	AppSettings::Instance()->SetLive(3);


	return m_running;
}

bool Game::Running()
{
	return  m_running;
}

void Game::Quit()
{
	m_running = false;
}

void Game::AddChild(OpenglGameObject * object)
{	
	Bullet* bullet = dynamic_cast<Bullet*>(object);
	if (bullet) 
	{
		this->m_bullets.push_back(bullet);
		return;
	}
	
	m_gameObjects.push_back(object);
}


void Game::HandleEvents()
{
	SDL_Event event;
	
		/* Poll for events. SDL_PollEvent() returns 0 when there are no  */
		/* more events on the event queue, our while loop will exit when */
		/* that occurs.                                                  */
		while (SDL_PollEvent(&event)) {
			/* We are only worried about SDL_KEYDOWN and SDL_KEYUP events */
			switch (event.type) {
			case SDL_KEYDOWN:
				std::cout<<"Key press detected\n";
				switch (event.key.keysym.sym)
				{
				case SDLK_w:
					m_player->MoveUp();
					break;

				case SDLK_a:
					m_player->MoveLeft();
					break;

				case SDLK_d:
					m_player->MoveRigth();
					break;			
				
				default:
					break;
				}
				break;

			case SDL_KEYUP:
				cout<<"Key release detected\n";
				switch (event.key.keysym.sym)
				{
				case SDLK_c :
					m_player->SwitchPlayer();
					AppSettings::Instance()->SetModelLiveIcon(m_player->GetPoints());
					break;

				case SDLK_SPACE:
					m_player->Shoot();
					break;

				
				default:
					break;
				}
				break;

			
			case SDL_QUIT:
				m_running = false;
				break;

			default:
				break;
			}
		}
}

void Game::Update()
{
	//Player collision
	for (unsigned int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->Update(DESIRED_FRAME_RATE);
		Asteroid* asteroid = dynamic_cast<Asteroid*>(m_gameObjects[i]);
		
		//Checking if player is collading with the asteroid
		if (asteroid) 
		{
			if (m_player->IsCollading(asteroid)) 
			{
				Asteroid::AsteroidSize::Size asteroidSize = asteroid->GetSize();
				m_gameObjects.erase(m_gameObjects.begin()+i);
				CreateDebris(asteroidSize, Vector2D::Origin);
				m_player->Respawn();
				AppSettings::Instance()->ReduceLive();
				
			}

		}		
	}


	//Bullet collision
	Bullet* bullet;
	for (unsigned int x = 0; x < m_bullets.size(); x++)
	{
		bullet = m_bullets[x];
		bullet->Update(DESIRED_FRAME_RATE);
		for (unsigned int i = 0; i < m_gameObjects.size(); i++)
		{
			Asteroid* asteroid = dynamic_cast<Asteroid*>(m_gameObjects[i]);
			if (asteroid) 
			{
				if (bullet->IsCollading(asteroid)) 
				{
					std::cout << "THE BULLET IS COLLADING" << std::endl;
					this->ScoreLogic(asteroid);
					Asteroid::AsteroidSize::Size asteroidSize = asteroid->GetSize();
					//Deleting the asteroid
					m_gameObjects.erase(m_gameObjects.begin() + i);
					//Deleting the bullet
					m_bullets.erase(m_bullets.begin() + x);
					CreateDebris(asteroidSize, Vector2D::Origin);
					
				}
			}
		}
		//CHECKING IF THE LIVE OF THE BULLET IS OVER
		if (!bullet->isAlive())
		{
			this->m_bullets.erase(m_bullets.begin() + x);
		}
	}
}


void Game::Render()
{
	glClearColor(0.1f, 0.1f, 0.15f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	
	for each (GameObject*  gObject in m_gameObjects)
	{
		gObject->Render(GL_LINE_LOOP);
	}
	for each(Bullet* bullet in m_bullets)
	{
		bullet->Render(GL_POINTS);
	}
	AppSettings::Instance()->DrawLife(GL_LINE_LOOP);
	SDL_GL_SwapWindow(m_window);
}


void Game::Clean()
{
	std::cout << "cleaning game\n";
	SDL_GL_DeleteContext(m_context);
	SDL_DestroyWindow(m_window);
	m_gameObjects.clear();
	SDL_Quit();
}
#pragma endregion

#pragma region PRIVATE METHODS
bool Game::InitSDL()
{
	// Initialize SDL's Video subsystem
	//
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		std::cerr << "Failed to init SDL" << std::endl;
		return false;
	}

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

	Uint32 flags = SDL_WINDOW_OPENGL |
		SDL_WINDOW_SHOWN |
		SDL_WINDOW_RESIZABLE;

    this->m_window = SDL_CreateWindow(m_windowTitle.c_str(), m_windowXPos,m_windowYPos,m_windowWidth,m_windowHeight,flags);

	if (!m_window)
	{
		std::cerr << "Failed to create window!" << std::endl;
		SDL_Quit();
		return false;
	}

	m_context = SDL_GL_CreateContext(m_window);
	SDL_GL_MakeCurrent(m_window, m_context);

	// Make double buffer interval synced with vertical scanline refresh
	SDL_GL_SetSwapInterval(0);

	return true;
}


bool Game::InitGlew()
{
	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		std::cerr << "Error: " << glewGetErrorString(err) << std::endl;
		return false;
	}

	return true;
}


void Game::SetupViewPort()
{
	// Defining ortho values
	//
	float halfWidth = m_windowWidth * 0.5f;
	float halfHeight = m_windowHeight * 0.5f;

	// Set viewport to match window
	//
	glViewport(0, 0, m_windowWidth, m_windowHeight);

	// Set Mode to GL_PROJECTION
	//
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Set projection MATRIX to ORTHO
	//
	glOrtho(-halfWidth, halfWidth, -halfHeight, halfHeight, -1, 1);

	// Setting Mode to GL_MODELVIEW
	//
	glMatrixMode(GL_MODELVIEW);
}

void Game::CreatePlayers()
{
	
	auto dataplayers = AppSettings::Instance()->Initialize();

	//Setting up the ship physics
	RigidBodyComponent* ship_Physics = new RigidBodyComponent(
		Engine::Math::Vector2D(0.0f),
		Vector2D(0),
		1.0f,
		0.999f
		);

    m_player = new ShipPlayer(dataplayers, ship_Physics, new TransformationComponent(), Vector3(1.0f));
	this->m_gameObjects.push_back(m_player);
}

void Game::CreateAsteroids(int amount, Asteroid::AsteroidSize::Size size,Vector2D pos)
{
	for (int i = 0; i <  amount; i++)
	{
		Asteroid* asteroid = new Asteroid(size, pos);
		m_gameObjects.push_back(asteroid);
		asteroid->ApplayRandomTraslation();
		
	}
}

void Game::CreateDebris(Asteroid::AsteroidSize::Size size, Vector2D position)
{
	if (size == Asteroid::AsteroidSize::BIG)
	{
		CreateAsteroids(2, Asteroid::AsteroidSize::MEDIUM, position);
	}

	if (size == Asteroid::AsteroidSize::MEDIUM)
	{
		CreateAsteroids(2, Asteroid::AsteroidSize::SMALL, position);
	}
}

void Game::ScoreLogic(OpenglGameObject * object)
{
	Asteroid* asteroid = dynamic_cast<Asteroid*>(object);
	if(asteroid)
	{
		if(asteroid->GetSize() == Asteroid::AsteroidSize::BIG)
		{
			AppSettings::Instance()->AddScore(15);
		}
		else if(asteroid->GetSize() == Asteroid::AsteroidSize::MEDIUM)
		{
			AppSettings::Instance()->AddScore(10);
		}
		else if (asteroid->GetSize() == Asteroid::AsteroidSize::SMALL) 
		{
			AppSettings::Instance()->AddScore(5);
		}
	}

}

void Game::PlayerCollision()
{
}

void Game::BulletCollision()
{

}

#pragma endregion