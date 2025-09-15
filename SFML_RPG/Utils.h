#pragma once
#include "GraphicsSettings.h"

namespace utils {

	extern const GraphicsSettings* gfxSettings;

	template<typename T>
	const T p2pX(const T perc) {
		if(!gfxSettings)
			throw std::runtime_error("GraphicsSettings not initialized in utils");

		return static_cast<T>(static_cast<float>(perc) / 100.f * static_cast<float>(gfxSettings->resolution.size.x));
	}

	template<typename T>
	const T p2pY(const T perc) {
		if(!gfxSettings)
			throw std::runtime_error("GraphicsSettings not initialized in utils");

		return static_cast<T>(static_cast<float>(perc) / 100.f * static_cast<float>(gfxSettings->resolution.size.y));
	}

	const unsigned calcCharSize(float size);
	float distance(sf::Vector2f pos1, sf::Vector2f pos2);
}