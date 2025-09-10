#include "stdafx.h"
#include "GraphicsSettings.h"

GraphicsSettings::GraphicsSettings()
{
	title = "DEAFAULT";
	resolution = sf::VideoMode::getDesktopMode();
	fullscreen = false;
	verticalSync = false;
	frameRateLimit = 120;
	contextSettings.antiAliasingLevel = 0;
	videoModes = sf::VideoMode::getFullscreenModes();
}

void GraphicsSettings::updateResolution(sf::RenderWindow* window, int id)
{
	window->create(sf::VideoMode({ videoModes[id].size.x, videoModes[id].size.y }), title);
	resolution.size.x = videoModes[id].size.x;	
	resolution.size.y = videoModes[id].size.y;
}

void GraphicsSettings::loadFromFile(const std::string& filename)
{
	std::ifstream ifs(filename);

	if(ifs.is_open())
	{
		std::getline(ifs, title);
		ifs >> resolution.size.x >> resolution.size.y;
		ifs >> fullscreen;
		ifs >> frameRateLimit;
		ifs >> verticalSync;
		ifs >> contextSettings.antiAliasingLevel;
	}

	ifs.close();
}

void GraphicsSettings::saveToFile(const std::string& filename) const
{
	std::ofstream ofs(filename);

	if (ofs.is_open())
	{
		ofs << title;
		ofs << resolution.size.x << " " << resolution.size.y;
		ofs << fullscreen;
		ofs << frameRateLimit;
		ofs << verticalSync;
		ofs << contextSettings.antiAliasingLevel;
	}

	ofs.close();
}
