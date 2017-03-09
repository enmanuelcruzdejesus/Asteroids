#pragma once
#ifndef _ShipPlayer_
#define _ShipPlayer_
#include "OpenglGameObject.h"
class ShipPlayer: public OpenglGameObject
{
public :
	ShipPlayer(vector<Vector2D> points);
	ShipPlayer(vector<Vector2D>points, RigidBodyComponent* physics, TransformationComponent* transforms, Vector3 color);
	ShipPlayer(vector<vector<Vector2D>>players,RigidBodyComponent* physics, TransformationComponent* tranforms, Vector3 color);
	~ShipPlayer();
	void setPlayers(vector<vector<Vector2D>> players);
	void Update(double deltaTime)override;
	void Render(int mode)override;
	void Clean();
	void MoveUp();
	void MoveLeft();
	void MoveRigth();
	void MoveDown();
	void SwitchPlayer();
private:
	int m_currentIndexPlayer;
	vector<vector<Vector2D>> m_players;
};
#endif // !_ShipPlayer_

