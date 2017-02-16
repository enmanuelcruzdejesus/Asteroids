#pragma once
#include "Entity.h"
#include "Vector2D.h"
namespace Asteroids 
{
	namespace Entities
	{
		class Ship : public Entity
		{
		public:
			/*
			* CONS
			*/
			Ship(const std::vector<Engine::Math::Vector2D> points);

			/*
			* FUNCTIONS
			*/
			void MoveUp();
			void Draw();
		private:
			std::vector<Engine::Math::Vector2D> m_points;
		};
    }
}