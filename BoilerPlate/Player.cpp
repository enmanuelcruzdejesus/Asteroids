#include "Player.h"

Player::Player(vector<Vector2D> points):OpenglGameObject(points)
{
}

Player::Player(vector<Vector2D> points, RigidBodyComponent * physics, TransformationComponent * transforms, Vector3 color):
OpenglGameObject(m_points,physics,transforms,color)
{
}

void Player::Update(double deltaTime)
{

}

void Player::Render(int mode)
{
}

void Player::MoveUp()
{
}

void Player::MoveLefth()
{
}

void Player::MoveRigth()
{
}

void Player::MoveDown()
{
}
