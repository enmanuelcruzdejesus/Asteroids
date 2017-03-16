
#include "Game.h"
#include "glew.h"
#include "SDL_opengl.h"
#include "AppConfig.h"
#include "Entity.h"
#include "string"
#include <algorithm>
using namespace Engine::Math;
using namespace Asteroids::Entities;
using namespace Asteroids::Utilities;

const float DESIRED_FRAME_RATE = 60.0f;
const float DESIRED_FRAME_TIME = 1.0f / DESIRED_FRAME_RATE;
Game* Game::m_instance = 0;


//CTOR
Game::Game()
{
	
}

Game::~Game()
{
	clean();
	delete m_instance;
	m_instance = nullptr;
}

//GETTERS AND SETTERS

std::string Game::getWindowTitle()
{
	return m_windowTitle;
}

int Game::getWindowXPos()
{
	return m_windowXPos;
}

int Game::getWindowYPos()
{
	return m_windowYPos;
}

int Game::getWindowWidth()
{
	return m_windowWidth;
}

int Game::getWindowHeight()
{
	return m_windowHeight;
}

void Game::setWindowTitle(std::string gameTitle)
{
	m_windowTitle = gameTitle;
}

void Game::setWindowXPos(int xpos)
{
	m_windowXPos = xpos;
}

void Game::setWindowYPos(int ypos)
{
	m_windowYPos = ypos;
}

void Game::setWindowWidth(int width)
{
	m_windowWidth = width;
}

void Game::setWindowHeight(int height)
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



//*****PUBLIC FUNCTIONS*****/
bool Game::init(const char * title, int xpos, int ypos, int width, int height)
{

	setWindowTitle(title);
	setWindowXPos(xpos);
	setWindowYPos(ypos);
	setWindowWidth(width);
	setWindowHeight(height);

	// Init the external dependencies
	//
	bool success = initSDL() && initGlew();
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
	CreateAsteroids(10, Asteroid::AsteroidSize::BIG,Vector2D::Origin);


	return m_running;
}

bool Game::running()
{
	return  m_running;
}

void Game::quit()
{
	m_running = false;
}

void Game::AddChild(OpenglGameObject * object)
{
	this->m_gameObjects.push_back(object);
}


void Game::handleEvents()
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
				case SDLK_SPACE:
					m_player->Shoot();
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

void Game::update()
{
	for (unsigned int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->Update(DESIRED_FRAME_RATE);
		Asteroid* asteroid = dynamic_cast<Asteroid*>(m_gameObjects[i]);
		if (asteroid) 
		{
			if (m_player->IsCollading(asteroid)) 
			{
				Asteroid::AsteroidSize::Size asteroidSize = asteroid->GetSize();
				m_gameObjects.erase(m_gameObjects.begin()+i);
				CreateDebris(asteroidSize, Vector2D::Origin);
				m_player->Respawn();
				
			}
		}
	}
}


void Game::render()
{
	glClearColor(0.1f, 0.1f, 0.15f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	
	for each (GameObject*  gObject in m_gameObjects)
	{
		gObject->Render(GL_LINE_LOOP);
	}

	SDL_GL_SwapWindow(m_Window);
}


void Game::clean()
{
	std::cout << "cleaning game\n";
	SDL_GL_DeleteContext(m_context);
	SDL_DestroyWindow(m_Window);
	//InputHandler::Instance()->clean();
	m_gameObjects.clear();
	SDL_Quit();
}
\

//******PRIVATE FUNCTIONS******/

bool Game::initSDL()
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

    this->m_Window = SDL_CreateWindow(m_windowTitle.c_str(), m_windowXPos,m_windowYPos,m_windowWidth,m_windowHeight,flags);

	if (!m_Window)
	{
		std::cerr << "Failed to create window!" << std::endl;
		SDL_Quit();
		return false;
	}

	m_context = SDL_GL_CreateContext(m_Window);
	SDL_GL_MakeCurrent(m_Window, m_context);

	// Make double buffer interval synced with vertical scanline refresh
	SDL_GL_SetSwapInterval(0);

	return true;
}


bool Game::initGlew()
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
	AppConfig* app = new AppConfig();
	auto dataplayers = app->Initialize();

	//Setting up the ship physics
	RigidBodyComponent* ship_Physics = new RigidBodyComponent(
		Engine::Math::Vector2D(0.0f),
		Vector2D(0),
		1.0f,
		0.999f
		);

    m_player = new ShipPlayer(dataplayers, ship_Physics, new TransformationComponent(), Vector3(1.0f));
	this->m_gameObjects.push_back(m_player);
	delete app;
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



