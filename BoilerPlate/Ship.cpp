#include "Ship.h"
#include <SDL_opengl.h>

namespace Asteroids
{
	namespace Entities
	{
		Ship::Ship(const std::vector<Engine::Math::Vector2D> points)
			: m_points(points)
		{}

		void Ship::MoveUp()
		{
			/*Engine::Math::Vector2D velocity = Engine::Math::Vector2D(0, 1);
			Engine::Math::Vector2D newPos =
				m_position + velocity;

			Entity::Translate(newPos);*/
		}

		void Ship::Draw()
		{
			/*Entity::Draw(GL_LINE_LOOP, m_points);*/
		}
	}
}