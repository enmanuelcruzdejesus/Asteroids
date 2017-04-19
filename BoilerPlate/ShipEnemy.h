#pragma once
#ifndef _SHIP_ENEMY_
#define _SHIP_ENEMY_
#include "OpenglGameObject.h"
class ShipEnemy : public OpenglGameObject 
{
public:
	ShipEnemy();
	void Update(double deltaTime)override;
	void Render(int mode)override;
	void Clean();
	void Shoot();
private:
	int m_countDistanceX;
	int m_countDistanceY;
	void GeneratePoints();	
};
#endif
