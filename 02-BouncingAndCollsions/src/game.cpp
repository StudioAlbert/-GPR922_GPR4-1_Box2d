#include "game.h"

const float Game::pixelsMetersRatio = 100.0f;

Game::Game() :
	_up(*this, this->window_),
	_down(*this, this->window_),
	_left(*this, this->window_),
	_right(*this, this->window_),
	_world(b2Vec2(0, 0))
{

}

void Game::init() {

	window_.create(sf::VideoMode(1280, 720), "SAE Platformer");
	window_.setVerticalSyncEnabled(true);
	window_.setFramerateLimit(60.0f);

	// Init all elements
	//theBall.init(window_);
	b2Vec2 winSize(pixelsToMeters(window_.getSize().x), pixelsToMeters(window_.getSize().y));

	_up.init(b2Vec2(winSize.x, 1.0F), b2Vec2(winSize.x / 2.0f, 0.0F));
	_down.init(b2Vec2(winSize.x, 1.0F), b2Vec2(winSize.x / 2.0f, -1 * winSize.y));
	_left.init(b2Vec2(1.0F, winSize.y), b2Vec2(0.0F, -1 * winSize.y / 2.0F));
	_right.init(b2Vec2(1.0F, winSize.y), b2Vec2(winSize.x, -1 * winSize.y / 2.0F));

	_world.SetContactListener(&_contactListener);

}

void Game::loop()
{

	while (window_.isOpen())
	{
#pragma region Event processes
		sf::Event event;

		while (window_.pollEvent(event))
		{
			// Windows events -------------------------------------------------------------------------------
			if (event.type == sf::Event::Closed)
			{
				window_.close();
				return;
			}
			if (event.type == sf::Event::Resized)
			{
				auto view = window_.getView();
				view.setSize(event.size.width, event.size.height);
				window_.setView(view);
			}
		}


		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			// Mouse events ---------------------------------------------------------------------------------
			_greenBalls.emplace_back(sf::Vector2f(sf::Mouse::getPosition(window_).x, sf::Mouse::getPosition(window_).y), *this);

			_redBalls.emplace_back(sf::Vector2f(sf::Mouse::getPosition(window_).x, sf::Mouse::getPosition(window_).y), *this);
		}
#pragma endregion


#pragma region Physical process
		// Updating the world with a delay
		float timeStep = 1.0f / 60.0f;
		int32 velocityIterations = 6;
		int32 positionIterations = 2;
		_world.Step(timeStep, velocityIterations, positionIterations);

		// Update the elements

		std::erase_if(_greenBalls, [](Ball& ball) { return ball.IsDead(); });
		for (auto& ball : _greenBalls)
			ball.update();

		std::erase_if(_redBalls, [](Ball& ball) { return ball.IsDead(); });
		for (auto& ball : _redBalls)
			ball.update();

		_up.update();
		_down.update();
		_left.update();
		_right.update();

#pragma endregion


#pragma region Graphics process
		// Clear all backgroundb
		window_.clear();

		// Render All elements
		_up.render();
		_down.render();
		_left.render();
		_right.render();

		// Display all elements
		for (auto& ball : _greenBalls)
			window_.draw(ball);

		for (auto& ball : _redBalls)
			window_.draw(ball);

		window_.display();
#pragma endregion

	}
}

b2Vec2 Game::pixelsToMeters(sf::Vector2f pixels)
{
	return b2Vec2(pixels.x / pixelsMetersRatio, -1.0f * pixels.y / pixelsMetersRatio);
}

b2Vec2 Game::pixelsToMeters(sf::Vector2u pixels)
{
	return b2Vec2(pixels.x / pixelsMetersRatio, -1.0f * pixels.y / pixelsMetersRatio);
}

float Game::pixelsToMeters(float pixels)
{
	return pixels / pixelsMetersRatio;
}

sf::Vector2f Game::metersToPixels(b2Vec2 meters)
{
	return sf::Vector2f(meters.x * pixelsMetersRatio, -1.0f * meters.y * pixelsMetersRatio);
}

sf::Vector2u Game::GetWinSize() const
{
	return window_.getSize();
}

