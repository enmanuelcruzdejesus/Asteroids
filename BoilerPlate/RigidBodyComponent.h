#pragma once
#ifndef _PHYSICS_COMPONENT_H_
#define _PHYSICS_COMPONENT_H_
#include "Vector2D.h"
using namespace Engine::Math;

class RigidBodyComponent 
{
public:
	/* =============================================================
	* CTOR
	* ============================================================= */
	RigidBodyComponent();
	RigidBodyComponent(Vector2D gravity,Vector2D position, float mass = 1.0f, float dragFactor = 1.0f);
	~RigidBodyComponent();

	/* =============================================================
	* PUBLIC FUNCTIONS
	* ============================================================= */
	void Update(double deltaTime);
	void ApplyForce(const Vector2D force, float angleInRadians = 1.0f);

	/* =============================================================
	* SETTER FUNCTIONS
	* ============================================================= */
	void SetMass(float mass) { m_mass = mass; }
	void SetVelocity(Vector2D velocity) { m_velocity = velocity; }

	/* =============================================================
	* GETTER FUNCTIONS
	* ============================================================= */
	float GetMass() const { return m_mass; }
	float GetSpeed() const { return m_velocity.Length(); }
	Vector2D GetVelocity() const { return m_velocity; }
protected:
	/* =============================================================
	* MEMBERS
	* ============================================================= */
	float m_mass;
	float m_drag;
	Vector2D m_position;
	Vector2D m_force;
	Vector2D m_gravity;
	Vector2D m_velocity;
};
	


#endif // !PHYSICS_COMPONENT_HPP