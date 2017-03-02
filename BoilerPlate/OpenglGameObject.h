#pragma once
#ifndef _OpenglGameObject_
#define _OpenglGameObject_
#include "GameObject.h"
#include "iostream"
#include "vector"
#include "Vector2D.h"
#include "Vector3D.h"
using namespace std;
using namespace Engine::Math;
class OpenglGameObject : public GameObject
{
public:
	OpenglGameObject(vector<Vector2D> points, Vector2D position, Vector2D velocity, float angle, Vector3 color);
	~OpenglGameObject();
	virtual void Update();
	virtual void Render(int mode);
	virtual void Clean();
	Engine::Math::Vector2D getPosition();
	std::vector<Engine::Math::Vector2D> getPoints();
	Engine::Math::Vector2D getVelocity();
	Engine::Math::Vector2D getAcceleration();
	Engine::Math::Vector3 getColor();
	float getAngle();
	void setPosition(Engine::Math::Vector2D position);
	void setPoints(vector<Engine::Math::Vector2D> points);
	void setVelocity(Engine::Math::Vector2D velocity);
	void setAcceleration(Engine::Math::Vector2D acceleration);
	void setAngle(float angle);
	void setColor(Engine::Math::Vector3 color);

protected:
	Engine::Math::Vector2D m_position;
	std::vector<Engine::Math::Vector2D> m_points;
	Engine::Math::Vector2D m_velocity;
	Engine::Math::Vector2D m_aceleration;
	Engine::Math::Vector3 m_color;
	float m_angle;

};
#endif