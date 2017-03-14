#include "AABB.h"

AABB::AABB()
{
	m_x = 0;
	m_y = 0;
	m_width = 0;
	m_height = 0;
}

AABB::AABB(int x, int y, int width, int heigth)
	:m_x(x),m_y(y),m_width(width),m_height(heigth)
{
}

bool AABB::isColliding(AABB * rhs)
{
	return (m_x < rhs->m_x + rhs->m_width && m_x + m_width > rhs->m_x &&
		m_y < rhs->m_y + rhs->m_height && m_y + m_height > rhs->m_y);
}

int AABB::GetX()
{
	return m_x;
}

int AABB::GetY()
{
	return m_y;
}

int AABB::GetWidth()
{
	return m_width;
}

int AABB::GetHeight()
{
	return m_height;
}

int AABB::GetMinX()
{
	return (m_width/2)-m_x;
}

int AABB::GetMinY()
{
	return (m_height/2)-m_y;
}

int AABB::GetMaxX()
{
	return m_x+m_width;
}

int AABB::GetMaxY()
{
	return m_y+m_height;
}

int AABB::SetX(int value)
{
	return m_x = value;
}

int AABB::SetY(int value)
{
	return m_y = value;
}

void AABB::Update(int x, int y)
{
	m_x = x;
	m_y = y;
}

