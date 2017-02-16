#include "Vector2D.h"
namespace Engine
{
	namespace Math 
	{
		Vector2D::Vector2D()
		{
		}
		Vector2D::Vector2D(float x, float y)
		{
			this->m_x = x;
			this->m_y = y;
		}
		float Vector2D::Length()
		{
			return this->m_length;
		}
		float Vector2D::GetX()
		{
			return this->m_x;;
		}
		float Vector2D::GetY()
		{
			return 	this->m_y;
		}
		Vector2D & Vector2D::operator=(const Vector2D & rigth)
		{
			
			// Prevent self assignment. Two objects
			// are equal if their memory address are equal.
			if (this == &rigth)
			{
				return *this;
			}

			m_x = rigth.m_x;
			m_y = rigth.m_y;

			return *this;
		}
		Vector2D & Vector2D::operator+=(const Vector2D & rigth)
		{
			m_x = m_x + rigth.m_x;
			m_y = m_y + rigth.m_y;

			return *this;
		}
		Vector2D & Vector2D::operator-=(const Vector2D & rigth)
		{

			m_x = m_x - rigth.m_x;
			m_y = m_y - rigth.m_y;
			return *this;
		}
		Vector2D & Vector2D::operator*=(const Vector2D & rigth)
		{
			m_x = m_x * rigth.m_x;
			m_y = m_y * rigth.m_y;
			return *this;
		}
		Vector2D & Vector2D::operator/=(const Vector2D & rigth)
		{
			m_x = m_x / rigth.m_x;
			m_y = m_y / rigth.m_y;
			return *this;
		}
		Vector2D Vector2D::operator+(const Vector2D & rigth)
		{
			Vector2D sum;

			sum.m_x = m_x + rigth.m_x;
			sum.m_y = m_y + rigth.m_y;

			return sum;
		}
		Vector2D Vector2D::operator-(const Vector2D & rigth)
		{
			Vector2D dif;

			dif.m_x = m_x + rigth.m_x;
			dif.m_y = m_y + rigth.m_y;

			return dif;
		}
		Vector2D Vector2D::operator-()
		{
			return Vector2D(-m_x, -m_y);
		}
		Vector2D Vector2D::operator*(const Vector2D & rigth)
		{
			Vector2D mul;

			mul.m_y = m_y * rigth.m_y;
			mul.m_x = m_x * rigth.m_x;

			return mul;
		}
		Vector2D Vector2D::operator/(const Vector2D & rigth)
		{
			Vector2D div;

			div.m_y = m_y / rigth.m_y;
			div.m_x = m_x / rigth.m_x;

			return div;
		}
		bool Vector2D::operator==(const Vector2D & rigth)
		{
			return m_x == rigth.m_x && m_y == rigth.m_y;
		}
		bool Vector2D::operator!=(const Vector2D & rigth)
		{
			return m_x != rigth.m_x ||
				m_y != rigth.m_y;;
		}
		Vector2D operator*(float scaleUnit, const Vector2D & rigth)
		{
			Vector2D scaled;
			scaled.m_x = scaleUnit * rigth.m_x;
			scaled.m_y = scaleUnit * rigth.m_y;

			return scaled;
		}
		Vector2D operator*(const Vector2D & left, float scaleUnit)
		{

			Vector2D scaled;
			scaled.m_x = scaleUnit * left.m_x;
			scaled.m_y = scaleUnit * left.m_y;

			return scaled;
		}
	}
}
