#include "OpenglGameObject.h"
#include "SDL_opengl.h"





OpenglGameObject::OpenglGameObject(vector<Vector2D> points) : m_points(points)
{
}

OpenglGameObject::OpenglGameObject(vector<Vector2D> points, RigidBodyComponent physic, TransformationComponent transport, Vector3 color):
m_points(points),
m_physics(physic),
m_transport(transport),
m_color(color)
{
}

OpenglGameObject::~OpenglGameObject()
{
}

void OpenglGameObject::Update()
{
	//m_velocity += m_aceleration;
	//m_position += m_velocity;
}

void OpenglGameObject::Render(int mode)
{
	// Reset transformation matrix to identity
	////
	//glLoadIdentity();

	//// Translate
	////
	//glTranslatef(m_position.GetX(),m_position.GetY(), 0.0f);

	//// Rotate
	////
	//glRotatef(m_angle, 0.0f, 0.0f, 1.0f);

	//// Change color
	////
	//glColor3f(m_color.x,m_color.y, m_color.z);

	//// Draw
	////
	//glBegin(mode);
	//for (auto point : m_points)
	//{
	//	glVertex2f(point.GetX(), point.GetY());
	//}
	//glEnd();
}

void OpenglGameObject::Clean()
{

}


void OpenglGameObject::setColor(Engine::Math::Vector3 color)
{
	m_color = color;
}
