#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Transformable.hpp>

#include "box2d/box2d.h"

class Player : public sf::Drawable, public sf::Transformable
{
public:
	Player() = default;
	Player(const sf::Vector2u& winSize, b2World& world);

	void MoveLeft();
	void MoveRight();
	void Stop();

	void Update(float);
	sf::FloatRect GetBounds() const;

	const sf::Vector2f& GetAcceleration();

protected:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	sf::Vector2f _winSize;

	sf::RectangleShape _shape;

	b2Body* _body;

	bool _outOfBounds();

};
