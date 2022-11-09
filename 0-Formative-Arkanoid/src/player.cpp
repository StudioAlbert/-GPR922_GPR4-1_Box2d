#include "player.h"

#include <iostream>
#include <ostream>

#include "SfmlToBox2d.h"

constexpr float ACC_VALUE = 15.0f;
constexpr float MAX_SPEED = 100.0f;

using namespace Utilities;


Player::Player(const sf::Vector2u& winSize, b2World& world) : _winSize(winSize)
{

	_shape = sf::RectangleShape(sf::Vector2f(60, 12));
	_shape.setFillColor(sf::Color(75, 30, 37));
	_shape.setOutlineColor(sf::Color(150, 60, 74));
	_shape.setOutlineThickness(1);
	_shape.setOrigin(_shape.getSize() * 0.5f);

	setPosition(_winSize.x * 0.5f, _winSize.y - 40);

	// Defing the box 2D elements
	b2BodyDef bodyDef;
	bodyDef.fixedRotation = true;
	bodyDef.type = b2_dynamicBody;
	bodyDef.linearDamping = 0.5f;

	b2Vec2 windowSize = SfmlToBox2d::PixelsToMeters(_winSize);

	bodyDef.position.Set(SfmlToBox2d::PixelsToMeters(getPosition().x), SfmlToBox2d::PixelsToMeters(getPosition().y));
	_body = world.CreateBody(&bodyDef);

	// Shape of the physical (A box)
	b2PolygonShape box;
	box.SetAsBox(SfmlToBox2d::PixelsToMeters(_shape.getSize().x * 0.5f), SfmlToBox2d::PixelsToMeters(_shape.getSize().y * 0.5f));

	// The fixture is what it defines the physic react
	b2FixtureDef ballFixtureDef;
	ballFixtureDef.shape = &box;
	ballFixtureDef.density = 1.0f;
	ballFixtureDef.friction = 10.0f;
	ballFixtureDef.restitution = 0.6f; // Make it bounce a little bit
	//playerFixtureDef.userData.pointer = reinterpret_cast <std::uintptr_t>(&playerBoxData);
	_body->CreateFixture(&ballFixtureDef);


}

void Player::Update(float timeElapsed)
{

	//std::cout << "body position [" << body->GetPosition().x << ":" << body->GetPosition().y
	//	<< "]|shape position [" << shape.getPosition().x << ":" << shape.getPosition().y << "]" << std::endl;

	// Get the position of the body
	b2Vec2 bodyPos = _body->GetPosition();
	// Translate meters to pixels
	sf::Vector2f graphicPosition = SfmlToBox2d::MetersToPixels(bodyPos);

	// Set the position of the Graphic object
	setPosition(graphicPosition);

	if (getPosition().x < _shape.getSize().x * 0.5f)
	{
		std::cout << "out of bounds Left" << std::endl;
		_body->SetTransform(b2Vec2(SfmlToBox2d::PixelsToMeters(getPosition().x - _shape.getSize().x * 0.5f), _body->GetPosition().y), _body->GetAngle());
	}

	if (getPosition().x > _winSize.x - _shape.getSize().x * 0.5f)
	{
		std::cout << "out of bounds Right" << std::endl;
		_body->SetTransform(b2Vec2(SfmlToBox2d::PixelsToMeters(_winSize.x - _shape.getSize().x * 0.5f), _body->GetPosition().y), _body->GetAngle());
	}


}

sf::FloatRect Player::GetBounds() const
{

	sf::FloatRect bounds = _shape.getGlobalBounds();

	bounds.left += getPosition().x;
	bounds.top += getPosition().y;

	return bounds;
}

const sf::Vector2f& Player::GetAcceleration()
{
	return SfmlToBox2d::MetersToPixels(_body->GetLinearVelocity());
}


void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform = getTransform();
	target.draw(_shape, states);
}

void Player::MoveLeft()
{
	_body->SetLinearVelocity(b2Vec2( - ACC_VALUE, 0));
	_body->SetLinearDamping(0.0f);
}

void Player::MoveRight()
{
	_body->SetLinearVelocity(b2Vec2(ACC_VALUE, 0));
	_body->SetLinearDamping(0.0f);

}

void Player::Stop()
{
	_body->SetLinearVelocity(b2Vec2(0, 0));
	_body->SetLinearDamping(0.9f);
}

bool Player::_outOfBounds()
{
	return (
		getPosition().x - _shape.getSize().x * 0.5f < 0 ||
		getPosition().x + _shape.getSize().x * 0.5f > _winSize.x ||
		getPosition().y - _shape.getSize().y * 0.5f < 0 ||
		getPosition().y + _shape.getSize().y * 0.5f > _winSize.y);
}


