#include "brick.h"

#include <SFML/Graphics/RenderTarget.hpp>

Brick::Brick(sf::Vector2f position, sf::Vector2f size, sf::Color fillColor, sf::Color outlineColor)
{
	setPosition(position);
	_shape = sf::RectangleShape(size);
	_shape.setOrigin(size * 0.5f);
	_shape.setFillColor(fillColor);
	_shape.setOutlineColor(outlineColor);
	_shape.setOutlineThickness(1);

}

sf::FloatRect Brick::GetBounds()
{
	sf::FloatRect bounds = _shape.getGlobalBounds();

	bounds.left += getPosition().x;
	bounds.top += getPosition().y;

	return bounds;

}

void Brick::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform = getTransform();
	target.draw(_shape, states);
}

