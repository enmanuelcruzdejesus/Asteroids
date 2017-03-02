#pragma once
#include "vector"
#include "Vector2D.h"

using namespace std;
using namespace Engine::Math;
namespace Asteroids 
{
	namespace Utilities 
	{
		class AppConfig 
		{
		public:
			AppConfig();
			std::vector<vector<Vector2D>> Initialize();
		private:
		
		};
	}
}