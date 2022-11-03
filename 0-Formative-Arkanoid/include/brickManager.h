#pragma once

#include <vector>
#include <SFML/Graphics/Drawable.hpp>
#include "brick.h"

class BrickManager : public sf::Drawable
{
public:
	void InitiateBricks(const sf::Vector2u& winSize);

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	std::vector<Brick>& GetBricks(){return _bricks;}

private:
	std::vector<Brick> _bricks;
};
