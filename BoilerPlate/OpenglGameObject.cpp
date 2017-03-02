#include "OpenglGameObject.h"
#include "SDL_opengl.h"



OpenglGameObject::OpenglGameObject(vector<Vector2D> points, Vector2D position, Vector2D velocity, float angle, Vector3 color):
m_points(points),
m_position(position),
m_velocity(velocity),
m_angle(angle),
m_color(color)
{
	
}

OpenglGameObject::~OpenglGameObject()
{
}

void OpenglGameObject::Update()
{
	m_velocity += m_aceleration;
	m_position += m_velocity;
}

void OpenglGameObject::Render(int mode)
{
	// Reset transformation matrix to identity
	//
	glLoadIdentity();

	// Translate
	//
	glTranslatef(m_position.GetX(),m_position.GetY(), 0.0f);

	// Rotate
	//
	glRotatef(m_angle, 0.0f, 0.0f, 1.0f);

	// Change color
	//
	glColor3f(m_color.x,m_color.y, m_color.z);

	// Draw
	//
	glBegin(mode);
	for (auto point : m_points)
	{
		glVertex2f(point.GetX(), point.GetY());
	}
	glEnd();
}

void OpenglGameObject::Clean()
{
	
}

Engine::Math::Vector2D OpenglGameObject::getPosition()
{
	return m_position;
}

vector<Engine::Math::Vector2D> OpenglGameObject::getPoints()
{
	return m_points;
}

Engine::Math::Vector2D OpenglGameObject::getVelocity()
{
	return m_velocity;
}

Engine::Math::Vector2D OpenglGameObject::getAcceleration()
{
	return m_aceleration;
}

Engine::Math::Vector3 OpenglGameObject::getColor()
{
	return m_color;
}

float OpenglGameObject::getAngle()
{
	return m_angle;
}

void OpenglGameObject::setPosition(Engine::Math::Vector2D position)
{
	m_position = position;
}

void OpenglGameObject::setPoints(vector<Engine::Math::Vector2D> points)
{
	m_points = points;
}

void OpenglGameObject::setVelocity(Engine::Math::Vector2D velocity)
{
	m_velocity = velocity;
}

void OpenglGameObject::setAcceleration(Engine::Math::Vector2D acceleration)
{
	m_aceleration = acceleration;
}

void OpenglGameObject::setAngle(float angle)
{
	m_angle = angle;
}

void OpenglGameObject::setColor(Engine::Math::Vector3 color)
{
	m_color = color;
}
