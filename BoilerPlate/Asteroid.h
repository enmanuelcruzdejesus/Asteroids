#pragma once
#ifndef _ASTEROID_
#define _ASTEROID_
#include "OpenglGameObject.h"

class Asteroid: public OpenglGameObject
{
public :
	struct AsteroidSize 
	{
		enum Size { BIG, MEDIUM, SMALL};
	};

	Asteroid(AsteroidSize::Size size , Vector2D pos, Vector3 color = Vector3(1.0f));
	Asteroid(vector<Vector2D> points);
	Asteroid(vector<Vector2D>points, RigidBodyComponent* physics, TransformationComponent* transforms, Vector3 color);
	~Asteroid();
    void Update(double deltaTime) override;
    void Render(int mode) override;

private:
	AsteroidSize::Size m_size;
	int m_sizeFactor;
	void GeneratePoints();
	void ApplayRandomImpulse();
};
#endif