#pragma once
#ifndef _Player_
#define _Player_
#include "OpenglGameObject.h"
class Player : public OpenglGameObject
{
public:
	Player(vector<Vector2D> points, Vector2D position, Vector2D velocity, float angle, Vector3 color);
   
};
#endif // !_Player_
