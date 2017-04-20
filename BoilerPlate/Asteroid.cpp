#include "Asteroid.h"
#include "MathUtilities.h"
#include "Game.h"



const int NUM_POINTS = 16;
const float MIN_SIZE = 25.0f;
const float MAX_SIZE = 45.0f;
const float ROTATION_SPEED =5.00f;



#pragma region CTOR AND DTOR
Asteroid::Asteroid(AsteroidSize::Size size, Vector2D  pos, Vector3 color)
{
	if (size == AsteroidSize::BIG) m_radius = 40.f;
	if (size == AsteroidSize::MEDIUM) m_radius = 20.f;
	if (size == AsteroidSize::SMALL) m_radius = 10.f;

	m_size = size;
	m_transforms = new TransformationComponent();
	m_transforms->Teleport(pos.GetX(), pos.GetY());
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

	m_collision = new AABB(m_transforms->GetPosition().GetX(), m_transforms->GetPosition().GetY(), m_radius,m_radius);
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

#pragma endregion

#pragma region METHODS
void Asteroid::Update(double deltaTime)
{
	float angle = m_transforms->GetAngleInDegrees() + ROTATION_SPEED;
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
	
	int x = Engine::Math::RandomInRange<int>(-0.01f, 0.01f);
	int y = Engine::Math::RandomInRange<int>(-0.01f, 0.01f);

	//Modify:
	//APPLAYING A INITIAL ACCELERATION TO THE ASTEROID
	m_physics->ApplyForce(
		Engine::Math::Vector2D(0.1),
		m_transforms->GetAngleIRadians()
		);
}

void Asteroid::ApplayRandomTraslation()
{
	int maxX = Game::Instance()->GetWindowWidth() / 2;
	int maxY = Game::Instance()->GetWindowHeight() / 2;
	int minX = -maxX;
	int minY = -maxY;

	int randomX = RandomInRange<int>(minX,maxX);
	int randomY = RandomInRange<int>(minY, maxY);


	m_transforms->Teleport(randomX, randomY);
}
#pragma endregion
