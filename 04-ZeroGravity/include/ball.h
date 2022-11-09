#pragma once

#include "SFML/Graphics.hpp"
#include "box2d/box2d.h"

class Game;

class Ball
{
public:
	explicit Ball(sf::RenderWindow& window_);

	void init(b2World& world);
	void update();
	void render();
	void setPixelsPosition(sf::Vector2f _pixelsPosition, sf::Vector2f _velocity);

	void move(float x, float y);

private:
	sf::CircleShape _shape;
	sf::RenderWindow& window;
	
	b2Body* body = nullptr;

};
