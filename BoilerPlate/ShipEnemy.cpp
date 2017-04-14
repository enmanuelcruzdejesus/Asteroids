#include "ShipEnemy.h"


ShipEnemy::ShipEnemy()
{
	m_radius = 10;
	m_transforms = new TransformationComponent();
	m_color = Vector3(1.0f);
	m_collision = new AABB(m_transforms->GetPosition().GetX(), m_transforms->GetPosition().GetY(), m_radius, m_radius);
	GeneratePoints();
}



void ShipEnemy::Update(double deltaTime)
{
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
