#pragma once
#include <random>

namespace Utilities
{

	class RNG
	{

	public:
		static float Range(float min, float max)
		{
			std::random_device dev;
			std::mt19937 rng = std::mt19937(dev());
			std::uniform_real_distribution<float> const dist(min,max);

			return dist(rng);

		}

		static int Range(int min, int max)
		{
			std::random_device dev;
			std::mt19937 rng = std::mt19937(dev());
			std::uniform_int_distribution<int> const dist(min, max);

			return dist(rng);

		}

		//template <>
		//static unsigned int Range<unsigned int>(unsigned int min, unsigned int max)
		//{
		//	std::random_device dev;
		//	std::mt19937 rng = std::mt19937(dev());
		//	std::uniform_int_distribution<int> const dist(min, max);

		//	return dist(rng);

		//}



	};

}