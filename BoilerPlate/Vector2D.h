#pragma once

#ifndef _VECTOR2D_H_
#define _VECTOR2D_H_

namespace Engine
{
	namespace Math
	{
		class Vector2D
		{
		public:
			/* =============================================================
			* STATIC
			* ============================================================= */
			static Vector2D Origin;

			/* =============================================================
			* CTOR
			* ============================================================= */
			Vector2D();
			Vector2D(float uniform);
			Vector2D(float x, float y);

			/* =============================================================
			* PUBLIC FUNCTIONS
			* ============================================================= */
			float Length() const;
			float SquaredLength() const;
			float Vector2D::Normalize();

			/* =============================================================
			* OPERATORS
			* ============================================================= */
			Vector2D& operator=(const Vector2D& rhs);
			Vector2D& operator+=(const Vector2D& rhs);
			Vector2D& operator-=(const Vector2D& rhs);
			Vector2D& operator*=(const Vector2D& rhs);
			Vector2D& operator/=(const Vector2D& rhs);
			Vector2D operator+(const Vector2D& rhs) const;
			Vector2D operator-(const Vector2D& rhs) const;
			Vector2D operator-() const;
			Vector2D operator*(const Vector2D& rhs) const;
			Vector2D operator/(const Vector2D& rhs) const;
			bool operator==(const Vector2D& rhs) const;
			bool operator!=(const Vector2D& rhs) const;
			friend Vector2D operator*(float scaleUnit, const Vector2D& rhs);
			friend Vector2D operator*(const Vector2D& lhs, float scaleUnit);

			/* =============================================================
			* MEMBERS
			* ============================================================= */
			float x;
			float y;
			float length;
		};
	}
}

#endif // !_VECTOR2_H_
