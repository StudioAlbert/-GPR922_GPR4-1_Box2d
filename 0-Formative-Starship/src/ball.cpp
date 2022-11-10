#include "ball.h"

#include <iostream>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Time.hpp>

#include "RNG.h"
#include "SFML_Vectors.h"

constexpr float RADIUS = 5;
constexpr float SPEED = 300;

Ball::Ball(const sf::Vector2u& winSize)
{

	_winSize = sf::Vector2f(winSize.x, winSize.y);

	_shape = sf::CircleShape(RADIUS);
	_shape.setOrigin(RADIUS, RADIUS);

	_direction.x = Utilities::RNG::Range(-1.0f, 1.0f);
	_direction.y = Utilities::RNG::Range(-1.0f, 1.0f);
	_direction = Utilities::SFML_Vectors::Normalize(_direction);

	setPosition(sf::Vector2f(_winSize.x * 0.5f, _winSize.y * 0.5f));
	
}


void Ball::Update(float timeElapsed)
{
	_velocity = _direction * SPEED;
	setPosition(getPosition() + _velocity * timeElapsed);
}

void Ball::CollideBounds()
{
	if (getPosition().x <= 0) 
	{
		_bounce(Utilities::SFML_Vectors::RIGHT);
	}
	if(getPosition().x >= _winSize.x)
	{
		_bounce(Utilities::SFML_Vectors::LEFT);
	}
	if (getPosition().y <= 0)
	{
		_bounce(Utilities::SFML_Vectors::DOWN);
	}
}

bool Ball::Collide(const sf::FloatRect& bounds)
{

	sf::Vector2f velocity = Utilities::SFML_Vectors::Normalize(_velocity) * _shape.getRadius();

	// TO DO : ????
	if (bounds.contains(getPosition() + velocity))
	{
		sf::Vector2f bounceDir = _getContactNormal(bounds, getPosition(), velocity);

		sf::Time time;
		_bounce(bounceDir);

		// Fake MTV -----------------------
		setPosition(getPosition() + _direction * 3.0f * _shape.getRadius());

		return true;

	}

	return false;

}

sf::Vector2f Ball::_getContactNormal(sf::FloatRect bounds, sf::Vector2f origin, sf::Vector2f direction)
{

	using namespace  Utilities::SFML_Vectors;

	// Get the edges of a float rect
	std::vector<sf::Vector2f> edges;
	edges.emplace_back(bounds.width, 0);
	edges.emplace_back(0, bounds.height);
	edges.emplace_back(bounds.width * -1, 0);
	edges.emplace_back(0, bounds.height * -1);

	sf::Vector2f bestEdge;
	double bestDot = std::numeric_limits<double>::max();

	for (auto edge : edges)
	{
		// TO DO : find the best edge !
		double localDot = Dot(direction, edge);
		std::cout << "dot/edge " << localDot << " : [" << edge.x << "," << edge.y << "]" << std::endl;

		if (localDot < bestDot)
		{
			bestDot = localDot;
			bestEdge = edge;
		}

	}

	std::cout << "Bests " << bestDot << " : [" << bestEdge.x << "," << bestEdge.y << "]" << std::endl;
	std::cout << "Direction : [" << direction.x << "," << direction.y << "]" << std::endl;

	sf::Vector2f normalizedNormalEdge = Normalize(LeftOrtho(bestEdge));

	return normalizedNormalEdge;
}

void Ball::_bounce(sf::Vector2f dir)
{
	std::cout << " : Bouncing direction : " << dir.x << ":" << dir.y << std::endl;

	float absX = std::abs(dir.x);
	float absY = std::abs(dir.y);

	if (absX > std::numeric_limits<float>::epsilon()) {
		//_direction.x = dir.x * std::abs(_direction.x);
		_direction.x *= -1;
	}
	if (absY > std::numeric_limits<float>::epsilon()) {
		//_direction.y = dir.y * std::abs(_direction.y);
		_direction.y *= -1;
	}

	_direction *= 1.025f; // 5% de plus à chaque rebond

}

bool Ball::IsOut()
{
	return getPosition().y >= _winSize.y;
}

void Ball::AddForce(sf::Vector2f force)
{
	_direction += force;
}


