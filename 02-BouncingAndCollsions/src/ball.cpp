
#include <iostream>

#include "ball.h"
#include "game.h"
#include "RNG.h"

Ball::Ball(sf::Vector2f pixelPos, Game& game_) : _game(game_)
{

    // Defining the shape
    _shape.setRadius(20.0f);
    _shape.setOrigin(_shape.getRadius(), _shape.getRadius());
    _shape.setFillColor(sf::Color::Red);

    // Defing the box 2D elements
    b2BodyDef bodyDef;
    bodyDef.fixedRotation = true;
    bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(Game::pixelsToMeters(pixelPos).x, Game::pixelsToMeters(pixelPos).y);
    //auto* m_userData = new ContactEvent(*this);
    //bodyDef.userData.pointer = reinterpret_cast<uintptr_t>(m_userData);

    body = _game.getWorld().CreateBody(&bodyDef);
    body->SetLinearVelocity(b2Vec2(Utilities::RNG::Range(-1.0f, 1.0f), Utilities::RNG::Range(-1.0f, 1.0f)));

    // Shape of the physical (A box)
    b2CircleShape ballBox;
    ballBox.m_radius = Game::pixelsToMeters(_shape.getRadius());

    // The fixture is what it defines the physic react
    b2FixtureDef playerFixtureDef;
    playerFixtureDef.shape = &ballBox;
    playerFixtureDef.density = 1.0f;
    playerFixtureDef.friction = 0.0f;
    playerFixtureDef.restitution = 0.6f; // Make it bounce a little bit

	ContactEvent* m_userData = new ContactEvent(*this);
    playerFixtureDef.userData.pointer = reinterpret_cast<uintptr_t>(m_userData);

    auto fixture = body->CreateFixture(&playerFixtureDef);
    //body->SetUserData(reinterpret_cast <std::uintptr_t>(this));

}

Ball::~Ball()
{
	_game.getWorld().DestroyBody(body);
}

Ball& Ball::operator=(const Ball& other)
{
	Ball ball(other);
	return ball;
}

void Ball::update() {
    
    //std::cout << "Ball position [" << body->GetPosition().x << ":" << body->GetPosition().y 
    //    << "]|shape position [" << shape.getPosition().x << ":" << shape.getPosition().y << "]" << std::endl;
    
    // Get the position of the body
    b2Vec2 bodyPos = body->GetPosition();
    // Translate meters to pixels
    sf::Vector2f graphicPosition = Game::metersToPixels(bodyPos);
    // Set the position of the Graphic object
	_shape.setPosition(graphicPosition);

}

void Ball::setPixelsPosition(sf::Vector2f _pixelsPosition) {
    // Put in mouse position
    body->SetTransform(Game::pixelsToMeters(_pixelsPosition), body->GetAngle());
    // Reset the velocity (Speed)
    body->SetLinearVelocity(b2Vec2(0.0f, -0.00001f));
}

void Ball::SetNewColor()
{
	_shape.setFillColor(sf::Color(rand() % 255, rand() % 255, rand() % 255));
}

void Ball::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    //states.transform = getTransform();
    target.draw(_shape);
}

void Ball::ContactReaction()
{
	std::cout << "Ball::ContactReaction" << std::endl;
}
