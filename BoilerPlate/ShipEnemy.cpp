#include "ShipEnemy.h"
#include <cmath>
#include <time.h>

#include "MathUtilities.h"
#include "Game.h"
#include "Bullet.h"
#include "Game.h"

const float THURST = 0.02f;
const float CONSTANT_FORCE(THURST);
const int SHOOT_TIME = 180;


ShipEnemy::ShipEnemy()
{

	m_updates = 0;

	m_radius = 10;

	//INITIAL PO
	m_transforms = new TransformationComponent(Vector2D(0,0),0);

	// Physics
	//
	m_physics = new RigidBodyComponent(
		Vector2D(0.0f), // No gravity
		m_transforms->GetPosition(),
		1.0f,
		1.0 // No friction
		);


	m_color = Vector3(1.0f);
	m_collision = new AABB(m_transforms->GetPosition().GetX(), m_transforms->GetPosition().GetY(), m_radius, m_radius);
	GeneratePoints();


	//Applaying Force
	this->m_physics->ApplyForce(CONSTANT_FORCE, m_transforms->GetAngleIRadians());



}


ShipEnemy::ShipEnemy(OpenglGameObject * target):
	m_target(target)
{

	m_updates = 0;

	m_radius = 10;

	//INITIAL PO
	m_transforms = new TransformationComponent(Vector2D(0, 0), 1);

	// Physics
	//
	m_physics = new RigidBodyComponent(
		Vector2D(0.0f), // No gravity
		m_transforms->GetPosition(),
		1.0f,
		1.0 // No friction
		);


	m_color = Vector3(1.0f);
	m_collision = new AABB(m_transforms->GetPosition().GetX(), m_transforms->GetPosition().GetY(), m_radius, m_radius);
	GeneratePoints();


	//Applaying Force
	//this->m_physics->ApplyForce(CONSTANT_FORCE, m_transforms->GetAngleIRadians());
}

void ShipEnemy::Update(double deltaTime)
{	
	if (m_updates == SHOOT_TIME)
	{
		Shoot();
		m_updates = 0;
	}
	else
	{
		this->m_updates++;
		OpenglGameObject::Update(deltaTime);

	}   	
}

void ShipEnemy::Render(int mode)
{
	OpenglGameObject::Render(mode);
}

void ShipEnemy::Clean()
{
	
}

void ShipEnemy::Shoot()
{
	if (this->m_target) 
	{
		int slope = (m_transforms->GetPosition().GetY() - m_target->GetPosition().GetY()) / (m_transforms->GetPosition().GetX() - m_target->GetPosition().GetX());
		int angleInRadians =  atan(slope) * 180 / PI;

		Bullet* bullet = new Bullet(m_transforms->GetPosition(), Vector2D(THURST), angleInRadians);
		Game::Instance()->AddChild(bullet);
		

	}
}

void ShipEnemy::GeneratePoints()
{
	m_points.push_back(Vector2D(10,10));
	m_points.push_back(Vector2D(30, 10));
	m_points.push_back(Vector2D(10, 15));
	m_points.push_back(Vector2D(20, 15));
	m_points.push_back(Vector2D(25, 25));
	m_points.push_back(Vector2D(30, 15));	

}
