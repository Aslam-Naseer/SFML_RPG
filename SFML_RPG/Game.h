#pragma once

#include "State.h"
#include "MainMenuState.h"
#include "GraphicsSettings.h"

class Game
{
private:

	sf::RenderWindow window;
	std::vector<sf::VideoMode> videoModes;

	sf::Clock clock;
	float dt;

	float gridSize;
	std::stack<State*> states;
	GraphicsSettings gfxSettings;
	std::map<std::string, sf::Keyboard::Scancode> supportedKeys;

	StateData stateData;

	void initGraphicsSettings();
	void initWindow();
	void initKeys();
	void initStateData();
	void initStates();

public:
	
	Game();
	~Game();

	void updateSfmlEvents();
	void update();
	void render();
	void run();
};

