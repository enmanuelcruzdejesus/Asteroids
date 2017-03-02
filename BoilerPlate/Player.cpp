#include "Player.h"

Player::Player(vector<Vector2D> points, Vector2D position, Vector2D velocity, float angle, Vector3 color) :
	OpenglGameObject(points, position, velocity, angle, color)
{
}

Player::~Player()
{
}

void Player::Update()
{
	OpenglGameObject::Update();
}

void Player::Render(int mode)
{
	OpenglGameObject::Render(mode);
}

void Player::Clean()
{
	OpenglGameObject::Clean();
}

void Player::MoveUp()
{
}

void Player::MoveLeft()
{
}

void Player::MoveDown()
{
}

void Player::MoveRigth()
{
}
