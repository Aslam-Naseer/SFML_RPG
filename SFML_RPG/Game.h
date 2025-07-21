#pragma once

#include "State.h"

class Game
{
private:

	sf::RenderWindow window;

	sf::Clock clock;
	float dt;

	std::stack<State*> states;
	std::map<std::string, sf::Keyboard::Scancode> supportedKeys;

	void initWindow();
	void initKeys();
	void initStates();

public:
	
	Game();
	~Game();

	void updateSfmlEvents();
	void update();
	void render();
	void run();
};

