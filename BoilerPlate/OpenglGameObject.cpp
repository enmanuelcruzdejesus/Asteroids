#include "OpenglGameObject.h"
#include "SDL_opengl.h"
#include "Game.h"
#include <cmath>



OpenglGameObject::OpenglGameObject():
m_transforms(nullptr),
m_physics(nullptr)
{
}

OpenglGameObject::OpenglGameObject(vector<Vector2D> points):
m_points(points),
m_transforms(nullptr),
m_physics(nullptr)
{
}

OpenglGameObject::OpenglGameObject(vector<Vector2D> points, RigidBodyComponent* physic, TransformationComponent* transport, Vector3 color):
m_points(points),
m_physics(physic),
m_transforms(transport),
m_color(color)
{
}

OpenglGameObject::~OpenglGameObject()
{
}

void OpenglGameObject::Update(double deltaTime)
{
	if (m_points.size() <= 0) return;
	
	float m_sceneHalfWidth = (Game::Instance()->getWindowWidth() / 2);
	float m_sceneHalfHeight = (Game::Instance()->getWindowHeight() / 2);

	if (!m_physics || !m_transforms) return;

	// Time stepping the position
	//
	Engine::Math::Vector2D newPos(
		m_transforms->GetPosition().x + (m_physics->GetVelocity().x * static_cast<float>(deltaTime)),
		m_transforms->GetPosition().y + (m_physics->GetVelocity().y * static_cast<float>(deltaTime))
		);

	// Getting axis limits
	//
	float worldMinX = -m_sceneHalfWidth;
	float worldMaxX = m_sceneHalfWidth;

	float worldMinY = -m_sceneHalfHeight;
	float worldMaxY = m_sceneHalfHeight;

	// Wrap!
	float x = wrap(newPos.x, worldMinX, worldMaxX);
	float y = wrap(newPos.y, worldMinY, worldMaxY);

	// Set the new position
	m_transforms->Teleport(x, y);

	//Updating collision points;
	this->m_collision->Update(this->m_transforms->GetPosition().x, this->m_transforms->GetPosition().y);

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
	glTranslatef(m_transforms->GetPosition().x, m_transforms->GetPosition().y, 0.0f);

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
		glVertex2f(point.x, point.y);
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


void OpenglGameObject::setColor(Engine::Math::Vector3 color)
{
	m_color = color;
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
