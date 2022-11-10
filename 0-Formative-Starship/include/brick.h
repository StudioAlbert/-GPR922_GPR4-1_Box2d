#pragma once
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

class Brick : public sf::Drawable, sf::Transformable
{
public:
	Brick(sf::Vector2f position, sf::Vector2f size, sf::Color fillColor, sf::Color outlineColor);

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	sf::FloatRect GetBounds();

private:
	sf::RectangleShape _shape;

};
