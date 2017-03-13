#pragma once
#include "Constants.h"

#include <random>
namespace Engine 
{
	namespace Math 
	{
		float DegreesToRadians(float angleInRadians);
		float RadiansToDegrees(float angleInDegrees);

		template<typename T>
		T RandomInRange(T min, T max)
		{
			//the random device that will seed the generator
			std::random_device seeder;

			//then make a mersenne twister engine
			std::mt19937 engine(seeder());

			//then the easy part... the distribution
			std::uniform_int_distribution<int> dist(static_cast<int>(min), static_cast<int>(max));

			return static_cast<T>(dist(engine));
		}
	}
}
