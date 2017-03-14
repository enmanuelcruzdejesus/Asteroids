#pragma once
#ifndef _AABB_
#define _AABB_
class AABB 
{
public:
	AABB();
	AABB(int x, int y, int width, int heigth);
	bool isColliding(AABB* rhs);
	int GetX() { return m_x; }
	int GetY() { return m_y; }
	int GetWidth() { return m_width; }
	int GetHeight() { return m_height; }
	int SetX(int value) { m_x = value;  }
	int SetY(int value) { m_y = value;  }
	void Update(int x, int y) { m_x = x; m_y = y; }
private :
	int m_x;
	int m_y;
	int m_width;
	int m_height;
};
#endif