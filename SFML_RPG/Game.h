#pragma once

#include <iostream>
#include <vector>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

class Game
{
private:

	sf::RenderWindow window;

	sf::Clock clock;
	float dt;

	void initWindow();

public:
	
	Game();
	~Game();

	void updateSfmlEvents();
	void update();
	void render();
	void run();
};

