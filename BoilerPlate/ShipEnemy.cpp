#include "ShipEnemy.h"
#include <cmath>
#include "MathUtilities.h"

const float THURST = 0.01f;
const float CONSTANT_FORCE(THURST);


ShipEnemy::ShipEnemy()
{
	m_radius = 10;

	//INITIAL POS
	m_transforms = new TransformationComponent(Vector2D(-550,300),0);

	// Physics
	//
	m_physics = new RigidBodyComponent(
		Vector2D(0.0f), // No gravity
		m_transforms->GetPosition(),
		1.0f,
		1.0f // No friction
		);


	m_color = Vector3(1.0f);
	m_collision = new AABB(m_transforms->GetPosition().GetX(), m_transforms->GetPosition().GetY(), m_radius, m_radius);
	GeneratePoints();


	//Applaying Force
	this->m_physics->ApplyForce(CONSTANT_FORCE, m_transforms->GetAngleIRadians());

}


void ShipEnemy::Update(double deltaTime)
{
	
	float y = sin(DegreesToRadians(m_transforms->GetPosition().GetX())) * 100;
	this->m_transforms->Teleport(m_transforms->GetPosition().GetX(), y);


	OpenglGameObject::Update(deltaTime);
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
