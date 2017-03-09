#include "ShipPlayer.h"
#include "MathUtilities.h"
const float ANGLE_OFFSET = 90.0f;
const float THRUST = 3.0f;
const float MAX_SPEED = 350.0f;

ShipPlayer::ShipPlayer(vector<Vector2D> points):OpenglGameObject(points){}

ShipPlayer::ShipPlayer(vector<Vector2D> points, RigidBodyComponent * physics, TransformationComponent * transforms, Vector3 color) :
	OpenglGameObject(points,physics,transforms,color){ this->m_currentIndexPlayer = 0;}

ShipPlayer::ShipPlayer(vector<vector<Vector2D>>players, RigidBodyComponent* physics, TransformationComponent* tranforms, Vector3 color) :
	OpenglGameObject(players.at(0),physics,tranforms,color)
{
	this->m_players = players;
	this->m_currentIndexPlayer = 0;
}


ShipPlayer::~ShipPlayer()
{
}

void ShipPlayer::setPlayers(vector<vector<Vector2D>> players)
{
	this->m_players = players;
	OpenglGameObject::m_points = this->m_players.at(0);
}

void ShipPlayer::Update(double deltaTime)
{
	
	OpenglGameObject::Update(deltaTime);
}

void ShipPlayer::Render(int mode)
{
	OpenglGameObject::Render(mode);
}

void ShipPlayer::Clean()
{
	OpenglGameObject::Clean();
}

void ShipPlayer::MoveUp()
{
	m_physics->ApplyForce(
		Engine::Math::Vector2D(THRUST),
		m_transforms->GetAngleIRadians() + Engine::Math::DegreesToRadians(ANGLE_OFFSET)
		);
}

void ShipPlayer::MoveLeft()
{
}

void ShipPlayer::MoveRigth()
{
}

void ShipPlayer::MoveDown()
{
}

void ShipPlayer::SwitchPlayer()
{
	if (!m_players.size() > 0) return;

	//Reseting index player
	if (this->m_currentIndexPlayer == m_players.size() - 1) 
	{
		this->m_currentIndexPlayer = 0;
		m_points = this->m_players[m_currentIndexPlayer];
		return;
	}

	m_currentIndexPlayer++;
	OpenglGameObject::m_points = this->m_players[m_currentIndexPlayer];	
}
