#pragma once
#include "Ship.h"

using namespace std;
namespace Asteroids 
{
	namespace Utilities 
	{
		class AppConfig 
		{
		public:
			std::vector<Entities::Ship*> Initialize();
		};
	}
}