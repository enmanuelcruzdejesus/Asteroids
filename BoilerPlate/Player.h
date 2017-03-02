#pragma once
#ifndef _Player_
#define _Player_
#include "OpenglGameObject.h"


class Player : public OpenglGameObject
{
public:
	Player(vector<Vector2D> points);
	Player(vector<Vector2D>points, RigidBodyComponent* physics, TransformationComponent* transforms, Vector3 color);
	void Update(double deltaTime) override;
	void Render(int mode) override;
	void MoveUp();
	void MoveLefth();
	void MoveRigth();
	void MoveDown();
   
};
#endif // !_Player_
