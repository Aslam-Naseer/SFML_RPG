#pragma once

class GraphicsSettings
{
public:
	std::string title;
	sf::VideoMode resolution;
	bool fullscreen;
	bool verticalSync;
	unsigned frameRateLimit;
	sf::ContextSettings contextSettings;
	std::vector<sf::VideoMode> videoModes;

	GraphicsSettings();

	void loadFromFile(const std::string& filename);
	void saveToFile(const std::string& filename) const;
};