#include "ShipPlayer.h"
#include "MathUtilities.h"


const float ANGLE_OFFSET = 90.0f;
const float THRUST = 0.01f;
const float MAX_SPEED = 0.12f;
const float ROTATION_SPEED = 5.0f;

ShipPlayer::ShipPlayer(vector<Vector2D> points):OpenglGameObject(points)
{
	m_radius = 10;

	m_transforms = new TransformationComponent();

	m_physics = new RigidBodyComponent(
		Engine::Math::Vector2D(0.0f),
		m_transforms->GetPosition(),
		1.0f,
		0.999f
		);

	m_color = Vector3(1.0f);

	CalculateMass();
}

ShipPlayer::ShipPlayer(vector<Vector2D> points, RigidBodyComponent * physics, TransformationComponent * transforms, Vector3 color) :
	OpenglGameObject(points,physics,transforms,color){

	m_radius = 10;
	this->m_currentIndexPlayer = 0;
	CalculateMass();
}

ShipPlayer::ShipPlayer(vector<vector<Vector2D>>players, RigidBodyComponent* physics, TransformationComponent* tranforms, Vector3 color) :
	OpenglGameObject(players.at(0),physics,tranforms,color)
{
	m_radius = 10;
	this->m_players = players;
	this->m_currentIndexPlayer = 0;

	CalculateMass();
}

ShipPlayer::~ShipPlayer(){}

void ShipPlayer::setPlayers(vector<vector<Vector2D>> players)
{
	this->m_players = players;
	OpenglGameObject::m_points = this->m_players.at(0);
}

void ShipPlayer::Update(double deltaTime)
{
	float speed = fabs(m_physics->GetSpeed());
	if (speed > MAX_SPEED)
	{
		m_physics->SetVelocity(
			Engine::Math::Vector2D(
				(m_physics->GetVelocity().x / speed) * MAX_SPEED,
				(m_physics->GetVelocity().y / speed) * MAX_SPEED
				)
			);

		m_currentSpeed = fabs(m_physics->GetVelocity().Length());
	}

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
	m_transforms->RotateInDegrees(m_transforms->GetAngleInDegrees() + ROTATION_SPEED);
}

void ShipPlayer::MoveRigth()
{
	m_transforms->RotateInDegrees(m_transforms->GetAngleInDegrees() - ROTATION_SPEED);
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

	//calculating the mass of the new player
	CalculateMass();
}

void ShipPlayer::CalculateMass()
{
	// Set the mass, proportional to the ship size (asumming points defines size)
	//
	this->m_physics->SetMass(m_points.size()/10);
}

