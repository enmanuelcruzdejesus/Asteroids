#include "Bullet.h"
const float THURST = 0.1f;
const float MAX_WIDTH = 15;
const float MAX_HEIGHT = 15;
Bullet::Bullet(Vector2D pos, Vector2D velocity, float AngleInRadians)
{

	this->m_transforms = new TransformationComponent();
	this->m_transforms->Teleport(pos.x,pos.y);
	this->m_transforms->RotateInRadians(AngleInRadians);


	this->m_physics = new RigidBodyComponent(
		Engine::Math::Vector2D(0.0f),
		m_transforms->GetPosition(),
		1.0f,
		0.999f
		);

	m_color = Vector3(1.0f);

	m_collision = new AABB(m_transforms->GetPosition().x, m_transforms->GetPosition().y, MAX_WIDTH, MAX_HEIGHT);

	GeneratePoints();

	//Applaying force 
	Vector2D force = Vector2D(THURST) + velocity;
	this->m_physics->ApplyForce(force, m_transforms->GetAngleIRadians());

	
}

void Bullet::Update(double deltaTime)
{

	OpenglGameObject::Update(deltaTime);
}

void Bullet::GeneratePoints()
{
	m_points.push_back(Vector2D(m_transforms->GetPosition().x, m_transforms->GetPosition().y));
}

void Bullet::ApplayInitialForce()
{
	

}
