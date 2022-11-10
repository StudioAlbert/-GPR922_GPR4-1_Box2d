#pragma once
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>

class Ball : public sf::Drawable, public sf::Transformable
{
public:
	Ball() = default;
	Ball(const sf::Vector2u& winSize);

	void Update(float);
	void CollideBounds();
	bool Collide(const sf::FloatRect& bounds);
	bool IsOut();
	void AddForce(sf::Vector2f);

protected:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	sf::Vector2f _winSize;

	sf::Vector2f _direction;
	sf::Vector2f _velocity;

	sf::CircleShape _shape;

	void _bounce(sf::Vector2f);
	sf::Vector2f _getContactNormal(sf::FloatRect bounds, sf::Vector2f origin, sf::Vector2f direction);

};
