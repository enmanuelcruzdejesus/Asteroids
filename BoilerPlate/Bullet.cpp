#include "Bullet.h"

#include "SDL_opengl.h"

#include "MathUtilities.h"
const float ANGLE_OFFSET = 90.0f;
const float THURST = 0.1f;
const float MAX_WIDTH = 15;
const float MAX_HEIGHT = 15;
const float MAX_FRAME_LIFE_TIME = 120;


#pragma region CTOR AND DTOR
Bullet::Bullet(Vector2D pos, Vector2D velocity, float AngleInRadians)
{

	this->m_isAlive = true;
    this->m_updates = 0;
	this->m_transforms = new TransformationComponent();
	this->m_transforms->Teleport(pos.GetX(),pos.GetY());
	this->m_transforms->RotateInRadians(AngleInRadians + DegreesToRadians(ANGLE_OFFSET));


	this->m_physics = new RigidBodyComponent(
		Engine::Math::Vector2D(0.0f),
		m_transforms->GetPosition(),
		1.0f,
		0.999f
		);

	m_color = Vector3(1.0f);

	m_collision = new AABB(m_transforms->GetPosition().GetX(), m_transforms->GetPosition().GetY(), MAX_WIDTH, MAX_HEIGHT);

	GeneratePoints();

	//Applaying force 
	Vector2D force = Vector2D(THURST) + velocity;
    this->m_physics->ApplyForce(force, m_transforms->GetAngleIRadians());
	
	
}
#pragma endregion

#pragma region METHODS
void Bullet::Update(double deltaTime)
{	 
	if (m_updates == MAX_FRAME_LIFE_TIME)
		m_isAlive = false;


	m_updates++;
	OpenglGameObject::Update(deltaTime);
}

void Bullet::Render(int mode)
{
	glLoadIdentity();
	glBegin(mode);
	glColor3f(m_color.x, m_color.y, m_color.z);
	glVertex2f(m_collision->GetMinX(), m_collision->GetMinY());
	glVertex2f(m_collision->GetMaxX(), m_collision->GetMinY());
	glVertex2f(m_collision->GetMaxX(), m_collision->GetMaxY());
	glVertex2f(m_collision->GetMinX(),m_collision->GetMaxY());
	glEnd();

	OpenglGameObject::Render(mode);
}

void Bullet::GeneratePoints()
{
	m_points.push_back(Vector2D(m_transforms->GetPosition().GetX(), m_transforms->GetPosition().GetY()));
}

void Bullet::ApplayInitialForce()
{
	

}

#pragma endregion