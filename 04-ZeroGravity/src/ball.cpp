
#include <iostream>

#include "ball.h"
#include "game.h"

Ball::Ball(sf::RenderWindow& window_) : window(window_)
{
}

void Ball::init(b2World& world) {

    // Defining the shape
	shape.setRadius(20.0f);
    shape.setOrigin(shape.getRadius(), shape.getRadius());
	shape.setFillColor(sf::Color::Red);
	shape.setFillColor(sf::Color::Red);

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

void Ball::update() {
    
    // Get the position of the body
    b2Vec2 bodyPos = body->GetPosition();

    // Translate meters to pixels
    sf::Vector2f graphicPosition = Game::metersToPixels(bodyPos);

    // Set the position of the Graphic object
	shape.setPosition(graphicPosition);

    std::cout << "Ball velocity : " << body->GetLinearVelocity().x << " : " << body->GetLinearVelocity().y << " : " << body->GetLinearVelocity().Length() << std::endl;

}

void Ball::render() {
	window.draw(shape);
}

void Ball::setPixelsPosition(sf::Vector2f _pixelsPosition, sf::Vector2f velocity_) {

    float magicNumber = 3.0f;

    // Put in mouse position
    body->SetTransform(Game::pixelsToMeters(_pixelsPosition), body->GetAngle());
    // Reset the velocity (Speed)
    b2Vec2 newb2Velocity = Game::pixelsToMeters(Vector2f(magicNumber * velocity_.x, magicNumber * velocity_.y));
    //b2Vec2 newb2Velocity(velocity_.x, velocity_.y);
    body->SetLinearVelocity(newb2Velocity);
}

void Ball::move(float x, float y)
{
    // Force position -----------------------------------------------
    //auto position = body->GetTransform().p;

    //position.x += x;
    //position.y += y * -1;

    //body->SetTransform(position, body->GetAngle());

    // Set Velocity ----------------------------------------------
    //float speed = 5.0f;
    //body->SetLinearVelocity(b2Vec2( x * speed, speed * y * -1));

    // Set forces -------------------------------------------------
    body->ApplyForceToCenter(b2Vec2(x, y * -1), true);

}
