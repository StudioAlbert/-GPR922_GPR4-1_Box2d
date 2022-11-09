#pragma once

#include <limits>

#include "SFML/Graphics.hpp"
#include "box2d/box2d.h"

class Game;

class Ball final : public sf::Drawable
{
public:
	Ball(Game& game_);

	void init(sf::RenderWindow& window);
	void update();

	void setPixelsPosition(sf::Vector2f _pixelsPosition);

	void setNewColor();

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	Game& _game;

	sf::CircleShape _shape;
	//sf::RenderWindow& window;

	b2Body* body = nullptr;

};
