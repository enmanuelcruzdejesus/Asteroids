#pragma once

#ifndef _VECTOR2_H_
#define _VECTOR2_H_

namespace Engine
{
	namespace Math
	{
		class Vector2D
		{
		public:
			/*
			* CONST
			*/
			Vector2D();
			Vector2D(float x, float y);

			/*
			* PUBLIC FUNCTIONS
			*/
			float Length();
		    float GetX();
		    float GetY();

			/*
			* OPERATORS
			*/
			Vector2D& operator=(const Vector2D& rigth);
			Vector2D& operator+=(const Vector2D& rigth);
			Vector2D& operator-=(const Vector2D& rigth);
			Vector2D& operator*=(const Vector2D& rigth);
			Vector2D& operator/=(const Vector2D& rigth);
			Vector2D operator+(const Vector2D& rigth);
			Vector2D operator-(const Vector2D& rigth);
			Vector2D operator-();			   
			Vector2D operator*(const Vector2D& rigth);
			Vector2D operator/(const Vector2D& rigth);
			bool operator==(const Vector2D& rigth);
			bool operator!=(const Vector2D& rigth);
			friend Vector2D operator*(float scaleUnit, const Vector2D& rigth);
			friend Vector2D operator*(const Vector2D& left, float scaleUnit);

		private:
			float m_x;
			float m_y;
			float m_length;
		};
	}
}

#endif // !_VECTOR2_H_
