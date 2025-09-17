#include "stdafx.h"
#include "utils.h"

namespace utils {
    const GraphicsSettings* gfxSettings = nullptr;

	const unsigned calcCharSize(float size)
	{
		if (!gfxSettings)
			throw std::runtime_error("GraphicsSettings not initialized in utils");

		if (size < 0.1f)
			size = 0.1f;
		else if (size > 5)
			size = 5;

		return static_cast<unsigned>((gfxSettings->resolution.size.x + gfxSettings->resolution.size.y) * size / 120);

	}

	float distance(sf::Vector2f pos1, sf::Vector2f pos2)
	{
		return sqrt(pow((pos1.x - pos2.x), 2) + pow((pos1.y - pos2.y),2));
	}

	float length(sf::Vector2f vec)
	{
		return sqrt(pow(vec.x,2) + pow(vec.y,2));
	}

	sf::Color getTextColor(const sf::Color& backgroundColor)
	{
		float luminance = (0.299f * backgroundColor.r +
			0.587f * backgroundColor.g +
			0.114f * backgroundColor.b) / 255.0f;

		return (luminance > 0.5f) ? sf::Color::Black : sf::Color::White;
	}
}