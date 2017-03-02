#pragma once
#ifndef _OpenglGameObject_
#define _OpenglGameObject_
#include "GameObject.h"
#include "iostream"
#include "vector"
#include "RigidBodyComponent.h"
#include "TransformationComponent.h"
using namespace std;
using namespace Engine::Math;
class OpenglGameObject : public GameObject
{
public:
	OpenglGameObject(vector<Vector2D> points);
	OpenglGameObject(vector<Vector2D>points,RigidBodyComponent physic, TransformationComponent transport, Vector3 color);
	~OpenglGameObject();
	virtual void Update();
	virtual void Render(int mode);
	virtual void Clean();	
	void setColor(Engine::Math::Vector3 color);

protected:
	Engine::Math::Vector2D m_position;
	std::vector<Engine::Math::Vector2D> m_points;
	RigidBodyComponent m_physics;
	TransformationComponent m_transport;
	Engine::Math::Vector3 m_color;
	float m_angle;

};
#endif