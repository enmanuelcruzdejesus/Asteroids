#include "TransformationComponent.h"
#include "iostream"
#include "MathUtilities.h"

	 const std::string COMP_NAME = "TRANSFORMATION_COMPONENT";

	TransformationComponent::TransformationComponent():
		 m_angleInDegrees(0)
		, m_angleInRadians(0)
	{}

	TransformationComponent::TransformationComponent(Vector2D position, float angleInDegrees)
	{
		Teleport(position);
		RotateInDegrees(angleInDegrees);
	}

	TransformationComponent::~TransformationComponent()
	{}

	void TransformationComponent::Teleport(float x, float y)
	{
		m_position.SetX(x);
		m_position.SetY(y);
	}

	void TransformationComponent::Teleport(Vector2D newPosition)
	{
		m_position = newPosition;
	}
	void TransformationComponent::RotateInDegrees(float angle)
	{
		m_angleInDegrees = angle;
		m_angleInRadians = (angle)* (PI / 180);
	}
	void TransformationComponent::RotateInRadians(float angle)
	{
		m_angleInRadians = angle;
		m_angleInDegrees = angle * (180 / PI);
	}

	void TransformationComponent::ResetOrientation()
	{
		m_angleInDegrees = 0;
		m_angleInRadians = 0;
	}

