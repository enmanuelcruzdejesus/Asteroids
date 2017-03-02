#include "Vector2D.h"
#include <cmath>



namespace Engine
{
	namespace Math
	{
		Vector2D Vector2D::Origin = Vector2D();

		Vector2D::Vector2D()
			: x(0.0f)
			, y(0.0f)
			, length(0.0f)
		{}

		Vector2D::Vector2D(float uniform)
			: x(uniform)
			, y(uniform)
			, length(0)
		{
			// Calculate length for the given point
			//
			Length();
		}

		Vector2D::Vector2D(float x, float y)
			: x(x)
			, y(y)
			, length(0)
		{
			// Calculate length for the given point
			//
			Length();
		}

		float Vector2D::Length() const
		{
			return std::sqrt(x * x + y * y);
		}

		float Vector2D::SquaredLength() const
		{
			return x * x + y * y;
		}

		float Vector2D::Normalize()
		{
			// Calculating the length
			Length();

			float inverseScale = 1.0f / length;
			x *= inverseScale;
			y *= inverseScale;

			return length;
		}

		// operators
		//
		Vector2D& Vector2D::operator=(const Vector2D& rhs)
		{
			// Prevent self assignment. Two objects
			// are equal if their memory address are equal.
			if (this == &rhs)
			{
				return *this;
			}

			x = rhs.x;
			y = rhs.y;

			return *this;
		}

		Vector2D& Vector2D::operator+=(const Vector2D& rhs)
		{
			x = x + rhs.x;
			y = y + rhs.y;

			return *this;
		}

		Vector2D& Vector2D::operator-=(const Vector2D& rhs)
		{
			x = x - rhs.x;
			y = y - rhs.y;

			return *this;
		}

		Vector2D& Vector2D::operator*=(const Vector2D& rhs)
		{
			x = x * rhs.x;
			y = y * rhs.y;

			return *this;
		}

		Vector2D& Vector2D::operator/=(const Vector2D& rhs)
		{
			x = x / rhs.x;
			y = y / rhs.y;

			return *this;
		}

		Vector2D Vector2D::operator+(const Vector2D& rhs) const
		{
			Vector2D sum;

			sum.x = x + rhs.x;
			sum.y = y + rhs.y;

			return sum;
		}

		Vector2D Vector2D::operator-(const Vector2D& rhs) const
		{
			Vector2D sub;
			sub.x = x - rhs.x;
			sub.y = y - rhs.y;

			return sub;
		}

		Vector2D Vector2D::operator-() const
		{
			return Vector2D(-x, -y);
		}

		Vector2D Vector2D::operator*(const Vector2D& rhs) const
		{
			Vector2D scaled;

			scaled.y = y * rhs.y;
			scaled.x = x * rhs.x;

			return scaled;
		}

		Vector2D Vector2D::operator/(const Vector2D& rhs) const
		{
			Vector2D inverseScaled;

			inverseScaled.x = x / rhs.x;
			inverseScaled.y = y / rhs.y;

			return inverseScaled;
		}

		bool Vector2D::operator==(const Vector2D& rhs) const
		{
			return
				x == rhs.x &&
				y == rhs.y;
		}

		bool Vector2D::operator!=(const Vector2D& rhs) const
		{
			return
				x != rhs.x ||
				y != rhs.y;
		}

		// friend functions
		Vector2D operator*(float scaleUnit, const Vector2D& rhs)
		{
			Vector2D scaled;
			scaled.x = scaleUnit * rhs.x;
			scaled.y = scaleUnit * rhs.y;

			return scaled;
		}

		Vector2D operator*(const Vector2D& lhs, float scaleUnit)
		{
			Vector2D scaled;
			scaled.x = scaleUnit * lhs.x;
			scaled.y = scaleUnit * lhs.y;

			return scaled;
		}
	}
}