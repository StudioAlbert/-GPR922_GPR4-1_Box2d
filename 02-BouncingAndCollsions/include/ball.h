#pragma once

#include <limits>

#include "SFML/Graphics.hpp"
#include "box2d/box2d.h"
#include "ContactEvent.h"

class Game;

class Ball : public sf::Drawable
{
public:
	Ball(Game& game_);
	~Ball() override;

	Ball& operator=(const Ball& other);

	//void init(sf::RenderWindow& window);
	void update();

	void setPixelsPosition(sf::Vector2f _pixelsPosition);

	void SetNewColor();

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	void ContactReaction();
	void SetDead() { _isDead = true; }
	bool IsDead() { return _isDead; }

	std::string _name = "ball";

private:
	Game& _game;
	b2Body* body = nullptr;
	bool _isDead = false;

protected:
	sf::CircleShape _shape;

};
