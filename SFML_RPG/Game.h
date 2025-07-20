#pragma once

#include "State.h"

class Game
{
private:

	sf::RenderWindow window;

	sf::Clock clock;
	float dt;

	std::stack<State*> states;

	void initWindow();
	void initStates();

public:
	
	Game();
	~Game();

	void updateSfmlEvents();
	void update();
	void render();
	void run();
};

