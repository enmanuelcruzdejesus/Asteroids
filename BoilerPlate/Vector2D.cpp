#include "Vector2D.h"
#include <cmath>



namespace Engine
{
	namespace Math
	{
		Vector2D Vector2D::Origin = Vector2D();

		Vector2D::Vector2D()
			: m_x(0.0f)
			, m_y(0.0f)
			, m_length(0.0f)
		{}

		Vector2D::Vector2D(float uniform)
			: m_x(uniform)
			, m_y(uniform)
			, m_length(0)
		{
			// Calculate length for the given point
			//
			Length();
		}

		Vector2D::Vector2D(float x, float y)
			: m_x(x)
			, m_y(y)
			, m_length(0)
		{
			// Calculate length for the given point
			//
			Length();
		}

		float Vector2D::GetX()
		{
			return m_x;
		}

		float Vector2D::GetY()
		{
			return m_y;
		}

		void Vector2D::SetX(float value)
		{
			m_x = value;
		}

		void Vector2D::SetY(float value)
		{
			m_y = value;
		}

		float Vector2D::Length() const
		{
			return std::sqrt(m_x * m_x + m_y * m_y);
		}

		float Vector2D::SquaredLength() const
		{
			return m_x * m_x + m_y * m_y;
		}

		float Vector2D::Normalize()
		{
			// Calculating the length
			Length();

			float inverseScale = 1.0f / m_length;
			m_x *= inverseScale;
			m_y *= inverseScale;

			return m_length;
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

			m_x = rhs.m_x;
			m_y = rhs.m_y;

			return *this;
		}

		Vector2D& Vector2D::operator+=(const Vector2D& rhs)
		{
			m_x = m_x + rhs.m_x;
			m_y = m_y + rhs.m_y;

			return *this;
		}

		Vector2D& Vector2D::operator-=(const Vector2D& rhs)
		{
			m_x = m_x - rhs.m_x;
			m_y = m_y - rhs.m_y;

			return *this;
		}

		Vector2D& Vector2D::operator*=(const Vector2D& rhs)
		{
			m_x = m_x * rhs.m_x;
			m_y = m_y * rhs.m_y;

			return *this;
		}

		Vector2D& Vector2D::operator/=(const Vector2D& rhs)
		{
			m_x = m_x / rhs.m_x;
			m_y = m_y / rhs.m_y;

			return *this;
		}

		Vector2D Vector2D::operator+(const Vector2D& rhs) const
		{
			Vector2D sum;

			sum.m_x = m_x + rhs.m_x;
			sum.m_y = m_y + rhs.m_y;

			return sum;
		}

		Vector2D Vector2D::operator-(const Vector2D& rhs) const
		{
			Vector2D sub;
			sub.m_x = m_x - rhs.m_x;
			sub.m_y = m_y - rhs.m_y;

			return sub;
		}

		Vector2D Vector2D::operator-() const
		{
			return Vector2D(-m_x, -m_y);
		}

		Vector2D Vector2D::operator*(const Vector2D& rhs) const
		{
			Vector2D scaled;

			scaled.m_y = m_y * rhs.m_y;
			scaled.m_x = m_x * rhs.m_x;

			return scaled;
		}

		Vector2D Vector2D::operator/(const Vector2D& rhs) const
		{
			Vector2D inverseScaled;

			inverseScaled.m_x = m_x / rhs.m_x;
			inverseScaled.m_y = m_y / rhs.m_y;

			return inverseScaled;
		}

		bool Vector2D::operator==(const Vector2D& rhs) const
		{
			return
				m_x == rhs.m_x &&
				m_y == rhs.m_y;
		}

		bool Vector2D::operator!=(const Vector2D& rhs) const
		{
			return
				m_x != rhs.m_x ||
				m_y != rhs.m_y;
		}

		// friend functions
		Vector2D operator*(float scaleUnit, const Vector2D& rhs)
		{
			Vector2D scaled;
			scaled.m_x = scaleUnit * rhs.m_x;
			scaled.m_y = scaleUnit * rhs.m_y;

			return scaled;
		}

		Vector2D operator*(const Vector2D& lhs, float scaleUnit)
		{
			Vector2D scaled;
			scaled.m_x = scaleUnit * lhs.m_x;
			scaled.m_y = scaleUnit * lhs.m_y;

			return scaled;
		}
	}
}