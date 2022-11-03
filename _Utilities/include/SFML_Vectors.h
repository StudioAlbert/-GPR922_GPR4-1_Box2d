#pragma once

namespace Utilities
{
	namespace SFML_Vectors
	{

		const sf::Vector2f UP = sf::Vector2f(0, -1);
		const sf::Vector2f DOWN = sf::Vector2f(0, 1);
		const sf::Vector2f LEFT = sf::Vector2f(-1, 0);
		const sf::Vector2f RIGHT = sf::Vector2f(1, 0);

		template <typename  T>
		T Normalize(T v1)
		{
			float magnitude = std::sqrt(v1.x * v1.x + v1.y * v1.y);
			T v2;

			v2.x = (float)v1.x / magnitude;
			v2.y = (float)v1.y / magnitude;

			return v2;
		}

		double Dot(const sf::Vector2f& v1, const sf::Vector2f& v2)
		{
			return v1.x * v2.x + v1.y * v2.y;
		}

		sf::Vector2f LeftOrtho(sf::Vector2f v)
		{
			return  sf::Vector2f(-v.y, v.x);
		}

		sf::Vector2f RightOrtho(sf::Vector2f v)
		{
			return  sf::Vector2f(v.y, -v.x);
		}
		
	}
}

