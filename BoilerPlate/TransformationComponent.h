#pragma once
#ifndef _TRANSFORMATION_COMPONENT_H_
#define _TRANSFORMATION_COMPONENT_H_

#include "Vector2D.h"
#include "Vector3D.h"
using namespace Engine::Math;



		class TransformationComponent 
		{
		public:
			/* =============================================================
			* PUBLIC FUNCTIONS
			* ============================================================= */
			TransformationComponent();
			TransformationComponent(Vector2D position, float angleInDegrees);
			~TransformationComponent();
			void Teleport(float x, float y);
			void Teleport(Vector2D newPosition);
			void RotateInDegrees(float angle);
			void RotateInRadians(float angle);
			void ResetOrientation();

			/* =============================================================
			* GETTER FUNCTIONS
			* ============================================================= */
			Vector2D GetPosition() const { return m_position; }
			float GetAngleInDegrees() const { return m_angleInDegrees; }
			float GetAngleIRadians() const { return m_angleInRadians; }
		protected:
			/* =============================================================
			* MEMBERS
			* ============================================================= */
			Vector2D m_position;
			Vector3 m_rotation;
			float m_angleInDegrees;
			float m_angleInRadians;
		};
	


#endif // !_TRANSFORMATION_COMPONENT_H_
