#include "OpenglGameObject.h"
#include "SDL_opengl.h"
#include "Game.h"
#include <cmath>


#pragma region CTOR AND DTOR
OpenglGameObject::OpenglGameObject():
m_transforms(nullptr),
m_physics(nullptr),
m_respawn(false)
{
}

OpenglGameObject::OpenglGameObject(vector<Vector2D> points):
m_points(points),
m_transforms(nullptr),
m_physics(nullptr),
m_respawn(false)
{
}

OpenglGameObject::OpenglGameObject(vector<Vector2D> points, RigidBodyComponent* physic, TransformationComponent* transport, Vector3 color):
m_points(points),
m_physics(physic),
m_transforms(transport),
m_color(color),
m_respawn(false)
{
}

OpenglGameObject::~OpenglGameObject()
{
}

#pragma endregion

#pragma region GETTERS AND SETTERS
void OpenglGameObject::setColor(Engine::Math::Vector3 color)
{
	m_color = color;
}
#pragma endregion

#pragma region  METHODS
void OpenglGameObject::Update(double deltaTime)
{
	if (m_points.size() <= 0) return;
	
	float m_sceneHalfWidth = (Game::Instance()->getWindowWidth() / 2);
	float m_sceneHalfHeight = (Game::Instance()->getWindowHeight() / 2);

	if (!m_physics || !m_transforms) return;

	// Time stepping the position
	//
	Engine::Math::Vector2D newPos(
		m_transforms->GetPosition().GetX() + (m_physics->GetVelocity().GetX() * static_cast<float>(deltaTime)),
		m_transforms->GetPosition().GetY() + (m_physics->GetVelocity().GetY() * static_cast<float>(deltaTime))
		);

	// Getting axis limits
	//
	float worldMinX = -m_sceneHalfWidth;
	float worldMaxX = m_sceneHalfWidth;

	float worldMinY = -m_sceneHalfHeight;
	float worldMaxY = m_sceneHalfHeight;

	// Wrap!
	float x = wrap(newPos.GetX(), worldMinX, worldMaxX);
	float y = wrap(newPos.GetY(), worldMinY, worldMaxY);

	// Set the new position
	m_transforms->Teleport(x, y);

	//Updating collision points;
	this->m_collision->Update(this->m_transforms->GetPosition().GetX(), this->m_transforms->GetPosition().GetY());

	this->m_physics->Update(deltaTime);

}


void OpenglGameObject::Render(int mode)
{
	if (m_points.size() <= 0) return;

	// Reset transformation matrix to identity
	//
	glLoadIdentity();

	// Translate
	//
	glTranslatef(m_transforms->GetPosition().GetX(), m_transforms->GetPosition().GetY(), 0.0f);

	// Rotate
	//
	glRotatef(m_transforms->GetAngleInDegrees(), 0.0f, 0.0f, 1.0f);

	// Change color
	//
	glColor3f(m_color.x, m_color.y, m_color.z);

	// Draw
	//
	glBegin(mode);
	for (auto point : m_points)
	{
		glVertex2f(point.GetX(), point.GetY());
	}
	glEnd();

	glLoadIdentity();
	glBegin(mode);
	glColor3f(m_color.x, m_color.y, m_color.z);
	glVertex2f(m_collision->GetMinX(), m_collision->GetMinY());
	glVertex2f(m_collision->GetMaxX(), m_collision->GetMinY());
	glVertex2f(m_collision->GetMaxX(), m_collision->GetMaxY());
	glVertex2f(m_collision->GetMinX(),m_collision->GetMaxY());
	glEnd();
}

void OpenglGameObject::Clean()
{
	
}



bool OpenglGameObject::CanCollide()
{
	return m_cancollide;
}

bool OpenglGameObject::IsCollading(OpenglGameObject * object)
{
	if(CanCollide())
	{
		return m_collision->isColliding(object->m_collision);

	}
	return false;
}


int OpenglGameObject::wrap(int axis, int min, int max)
{
	if (axis < min)
	{
		return max - (min - axis);
	}

	if (axis > max)
	{
		return min + (axis - max);
	}

	return axis;
}
#pragma endregion