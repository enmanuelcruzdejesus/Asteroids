#pragma once
#ifndef _BULLET_
#define _BULLET_
#include "OpenglGameObject.h"
class Bullet : public OpenglGameObject 
{
public:
	Bullet(Vector2D pos, Vector2D velocity, float AngleInRadians);
	void Update(double deltaTime) override;
	void Render(int mode)override;
	bool isAlive() { return m_isAlive; };
private:
	bool m_isAlive;
	int m_updates;
	void GeneratePoints();
	void ApplayInitialForce();
};
#endif