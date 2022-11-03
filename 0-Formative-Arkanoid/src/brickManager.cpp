#include "brickManager.h"

#include <SFML/Graphics/RenderTarget.hpp>

void BrickManager::InitiateBricks(const sf::Vector2u& winSize)
{

	sf::Vector2f size(40, 25);

	for(int x = 30; x < winSize.x; x += size.x * 1.1f)
	{
		for (int y = 30; y < 200; y += size.y * 1.1f)
		{
			_bricks.emplace_back(sf::Vector2f(x, y), size, sf::Color::White, sf::Color::Blue);
		}
	}

}

void BrickManager::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (const Brick& brick : _bricks)
	{
		target.draw(brick);
	}
}
