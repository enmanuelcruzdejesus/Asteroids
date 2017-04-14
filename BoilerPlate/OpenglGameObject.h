#pragma once
#ifndef _OpenglGameObject_
#define _OpenglGameObject_
#include "GameObject.h"
#include <iostream>
#include <vector>
#include "RigidBodyComponent.h"
#include "TransformationComponent.h"
#include "AABB.h"
using namespace std;
using namespace Engine::Math;
class OpenglGameObject : public GameObject
{
public:
	OpenglGameObject();
	OpenglGameObject(vector<Vector2D> points);
	OpenglGameObject(vector<Vector2D>points,RigidBodyComponent* physics, TransformationComponent* transforms, Vector3 color);
	~OpenglGameObject();
	virtual void Update(double deltaTime);
	virtual void Render(int mode);
	virtual void Clean();	
	void setColor(Engine::Math::Vector3 color);
	virtual bool CanCollide();
	virtual bool IsCollading(OpenglGameObject* object);
	bool IsRespawning() { return m_respawn; }
	void SetCanCollide(bool value) { m_cancollide = value;  }
	Vector2D GetPosition() { return m_transforms->GetPosition(); }
	std::vector<Vector2D> GetPoints() { return m_points; }
	

protected:
	int m_radius;
	bool m_cancollide;
	bool m_respawn;
	vector<Engine::Math::Vector2D> m_points;
	vector<GameObject*> m_components;
	RigidBodyComponent* m_physics;
	TransformationComponent* m_transforms;
	AABB* m_collision;
	Engine::Math::Vector3 m_color;
	int wrap(int x, int min, int max);

};
#endif