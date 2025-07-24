#pragma once

#include "MainMenuState.h"

class Game
{
private:

	sf::RenderWindow window;
	sf::Font font;

	sf::Clock clock;
	float dt;

	std::stack<State*> states;
	std::map<std::string, sf::Keyboard::Scancode> supportedKeys;

	void initWindow();
	void initKeys();
	void initStates();
	void initFonts();

public:
	
	Game();
	~Game();

	void updateSfmlEvents();
	void update();
	void render();
	void run();
};

