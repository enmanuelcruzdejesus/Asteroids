#pragma once
#ifndef _DRAWABLE2D_H_
#define _DRAWABLE2D_H_

// STDLIB
#include <vector>

// ENGINE
#include "Vector2D.h"

namespace Engine
{
	namespace Graphics
	{
		class Drawable2D
		{
		public:
			virtual void Translate(Math::Vector2D position);
			virtual void Draw(unsigned int mode, std::vector<Math::Vector2D> points);
		protected:
			Engine::Math::Vector2D m_position;
		};
	}
}

#endif // !_DRAWABLE_H_
