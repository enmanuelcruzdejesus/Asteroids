#include "OpenglGameObject.h"
#include "SDL_opengl.h"
#include "Game.h"




OpenglGameObject::OpenglGameObject(vector<Vector2D> points)
{
	m_points = points;
	m_physics = new RigidBodyComponent(
		Engine::Math::Vector2D(0.0f),
		m_transforms->GetPosition(),
		1.0f,
		0.999f
		);
	m_transforms = new TransformationComponent();
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

}


void OpenglGameObject::Render(int mode)
{

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
}

void OpenglGameObject::Clean()
{
	
}


void OpenglGameObject::setColor(Engine::Math::Vector3 color)
{
	m_color = color;
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
