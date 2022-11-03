
namespace Utilities
{
	namespace SfmlToBox2d
	{

		b2Vec2 PixelsToMeters(sf::Vector2f pixels)
		{
			return b2Vec2(pixels.x / pixelsMetersRatio, 1.0f * pixels.y / pixelsMetersRatio);
		}

		b2Vec2 PixelsToMeters(sf::Vector2u pixels)
		{
			return b2Vec2(pixels.x / pixelsMetersRatio, 1.0f * pixels.y / pixelsMetersRatio);
		}

		float PixelsToMeters(float pixels)
		{
			return pixels / pixelsMetersRatio;
		}

		sf::Vector2f MetersToPixels(b2Vec2 meters)
		{
			return sf::Vector2f(meters.x * pixelsMetersRatio, 1.0f * meters.y * pixelsMetersRatio);
		}



	}
}
