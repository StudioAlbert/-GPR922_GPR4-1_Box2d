
namespace Utilities
{
	namespace SfmlToBox2d
	{
		constexpr float PIXELS_METERS_RATIO = 100.0f;

		b2Vec2 PixelsToMeters(sf::Vector2f pixels)
		{
			return b2Vec2(pixels.x / PIXELS_METERS_RATIO, 1.0f * pixels.y / PIXELS_METERS_RATIO);
		}

		b2Vec2 PixelsToMeters(sf::Vector2u pixels)
		{
			return b2Vec2(pixels.x / PIXELS_METERS_RATIO, 1.0f * pixels.y / PIXELS_METERS_RATIO);
		}

		float PixelsToMeters(float pixels)
		{
			return pixels / PIXELS_METERS_RATIO;
		}

		sf::Vector2f MetersToPixels(b2Vec2 meters)
		{
			return sf::Vector2f(meters.x * PIXELS_METERS_RATIO, 1.0f * meters.y * PIXELS_METERS_RATIO);
		}



	}
}
