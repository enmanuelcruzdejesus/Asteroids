#pragma once
#ifndef _SHIP_ENEMY_
#define _SHIP_ENEMY_
#include "OpenglGameObject.h"
class ShipEnemy : public OpenglGameObject 
{
public:
	ShipEnemy();
	ShipEnemy(OpenglGameObject* target);
	void SetTarget(OpenglGameObject* target);
	void Update(double deltaTime)override;
	void Render(int mode)override;
	void Clean();
	void Shoot();
private:
	OpenglGameObject* m_target;
	int m_updates;
	void GeneratePoints();	
};
#endif
