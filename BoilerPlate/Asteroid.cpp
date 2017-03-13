#include "Asteroid.h"
#include "MathUtilities.h"
#include "Game.h"



const int NUM_POINTS = 16;
const float MIN_SIZE = 25.0f;
const float MAX_SIZE = 45.0f;
const float ROTATION_SPEED = 120.0f;

Asteroid::Asteroid(AsteroidSize::Size size, Vector2D  pos, Vector3 color)
{
	m_size = size;
	m_transforms = new TransformationComponent();
	m_transforms->Teleport(pos.x, pos.y);
	m_color = color;

	m_sizeFactor = static_cast<int>(size) + 1;

	// Physics
	//
	m_physics = new RigidBodyComponent(
		Vector2D(0.0f), // No gravity
		m_transforms->GetPosition(),
		1.0f,
		1.0f // No friction
		);

	GeneratePoints();
	ApplayRandomImpulse();
}

Asteroid::Asteroid(vector<Vector2D> points): OpenglGameObject(points)
{
}

Asteroid::Asteroid(vector<Vector2D> points, RigidBodyComponent * physics, TransformationComponent * transforms, Vector3 color):
	OpenglGameObject(points,physics,transforms,color)
{
}

Asteroid::~Asteroid()
{
}

void Asteroid::Update(double deltaTime)
{
	float angle = m_transforms->GetAngleInDegrees() + ROTATION_SPEED * deltaTime;
	m_transforms->RotateInDegrees(angle);

	OpenglGameObject::Update(deltaTime);
}

void Asteroid::Render(int mode)
{
	OpenglGameObject::Render(mode);
}

void Asteroid::GeneratePoints()
{
	// Calculating the MIN/MAX size of the asteroid based on the size enum value
	//
	float min = MIN_SIZE / m_sizeFactor;
	float max = MAX_SIZE / m_sizeFactor;

	// Randomly generate points for asteroid
	//
	for (int idx = 0; idx < NUM_POINTS; ++idx)
	{
		const float radians = (idx / static_cast<float>(NUM_POINTS)) * 2.0f * Engine::Math::PI;
		const float randDist = Engine::Math::RandomInRange<float>(min, max);

		m_points.push_back(Engine::Math::Vector2D(sinf(radians) * randDist, cosf(radians) * randDist));
	}
}

void Asteroid::ApplayRandomImpulse()
{
	float x = Engine::Math::RandomInRange<float>(-0.01f, 0.01f);
	float y = Engine::Math::RandomInRange<float>(-0.01f, 0.01f);

	m_physics->ApplyForce(
		Engine::Math::Vector2D(x, y) + static_cast<float>(m_sizeFactor),
		m_transforms->GetAngleIRadians()
		);
}

void Asteroid::ApplayRandomTraslation()
{
	int maxX = Game::Instance()->getWindowWidth() / 2;
	int maxY = Game::Instance()->getWindowHeight() / 2;
	int minX = -maxX;
	int minY = -maxY;

	int randomX = RandomInRange<int>(minX,maxX);
	int randomY = RandomInRange<int>(minY, maxY);

	m_transforms->Teleport(randomX, randomY);


		

}
