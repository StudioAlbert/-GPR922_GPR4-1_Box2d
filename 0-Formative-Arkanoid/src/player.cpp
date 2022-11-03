#include "player.h"

#include "SfmlToBox2d.h"

constexpr float ACC_VALUE = 150.0f;
constexpr float MAX_SPEED = 100.0f;


Player::Player(const sf::Vector2u& winSize, b2World& world) : _winSize(winSize)
{

	using namespace Utilities;

	_shape = sf::RectangleShape(sf::Vector2f(60, 12));
	_shape.setFillColor(sf::Color(75, 30, 37));
	_shape.setOutlineColor(sf::Color(150, 60, 74));
	_shape.setOutlineThickness(1);
	_shape.setOrigin(_shape.getSize() * 0.5f);

	_acceleration.x = 0;
	_acceleration.y = 0;

	setPosition(_winSize.x * 0.5f, _winSize.y - 40);

	// Defing the box 2D elements
	b2BodyDef bodyDef;
	bodyDef.fixedRotation = true;
	bodyDef.type = b2_dynamicBody;
	bodyDef.linearDamping = 0.5f;

	b2Vec2 windowSize = Game::pixelsToMeters(window.getSize());
	bodyDef.position.Set(windowSize.x / 2.0f, windowSize.y / 2.0f);
	body = world.CreateBody(&bodyDef);

	// Shape of the physical (A box)
	b2CircleShape ballBox;
	ballBox.m_radius = Game::pixelsToMeters(shape.getRadius());

	// The fixture is what it defines the physic react
	b2FixtureDef ballFixtureDef;
	ballFixtureDef.shape = &ballBox;
	ballFixtureDef.density = 1.0f;
	ballFixtureDef.friction = 10.0f;
	ballFixtureDef.restitution = 0.6f; // Make it bounce a little bit
	//playerFixtureDef.userData.pointer = reinterpret_cast <std::uintptr_t>(&playerBoxData);
	body->CreateFixture(&ballFixtureDef);


}

void Player::Update(float timeElapsed)
{

	if (std::abs(_speed.x) < MAX_SPEED)
	{
		_speed += _acceleration * timeElapsed;
	}

	setPosition(getPosition() + _speed);

	if (getPosition().x - _shape.getSize().x * 0.5f < 0)
	{
		setPosition(_shape.getSize().x * 0.5f, getPosition().y);
		
	}

	if (getPosition().x + _shape.getSize().x * 0.5f > _winSize.x)
	{
		setPosition(_winSize.x - _shape.getSize().x * 0.5f, getPosition().y);
	}

}

sf::FloatRect Player::GetBounds() const
{

	sf::FloatRect bounds = _shape.getGlobalBounds();

	bounds.left += getPosition().x;
	bounds.top += getPosition().y;

	return bounds;
}


void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform = getTransform();
	target.draw(_shape, states);
}

void Player::MoveLeft()
{
	_acceleration.x = -ACC_VALUE;
}

void Player::MoveRight()
{
	_acceleration.x = ACC_VALUE;
}

void Player::Stop()
{
	_acceleration.x = 0;
	_speed.x = 0;
}

bool Player::_outOfBounds()
{
	return (
		getPosition().x - _shape.getSize().x * 0.5f < 0 ||
		getPosition().x + _shape.getSize().x * 0.5f > _winSize.x ||
		getPosition().y - _shape.getSize().y * 0.5f < 0 ||
		getPosition().y + _shape.getSize().y * 0.5f > _winSize.y);
}


