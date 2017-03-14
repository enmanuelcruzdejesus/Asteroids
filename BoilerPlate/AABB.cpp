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

