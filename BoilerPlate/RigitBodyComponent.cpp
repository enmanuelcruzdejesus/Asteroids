#include "RigidBodyComponent.h"
#include "iostream"

	const std::string COMP_NAME = "PHYSICS_COMPONENT";
	RigidBodyComponent::RigidBodyComponent():
		  m_gravity(0.0f, 0.0f)
		, m_position(0.0f, 0.f)
		, m_mass(1.0f)
		, m_drag(1.0f)
	{}

	RigidBodyComponent::RigidBodyComponent(Vector2D gravity,Vector2D position, float mass, float drag):
		  m_mass(mass)
		, m_drag(drag)
		, m_position(position)
		, m_gravity(gravity)
	{}

	RigidBodyComponent::~RigidBodyComponent()
	{}

	void RigidBodyComponent::Update(double deltaTime)
	{
		// Apply acceleration
		//
		m_velocity += m_gravity;

		// Apply drag
		//
		m_velocity *= m_drag;

		// Base class function call
		//
	}

	void RigidBodyComponent::ApplyForce(Vector2D force, float angleInRadians)
	{
		if (m_mass > 0)
		{
			float x = (force.x / m_mass) * cosf(angleInRadians);
			float y = (force.y / m_mass) * sinf(angleInRadians);

			m_velocity += Vector2D(x, y);
		}
	}
	