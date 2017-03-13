#include "MathUtilities.h"

namespace Engine 
{
	namespace Math 
	{
		float Engine::Math::DegreesToRadians(float angleInRadians)
		{
			return angleInRadians * (PI / 180);
		}

		float Engine::Math::RadiansToDegrees(float angleInDegrees)
		{
			return angleInDegrees * (180/PI);
		}

	}
}

