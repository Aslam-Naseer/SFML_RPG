#pragma once

#include <iostream>
#include <vector>
#include <map>
#include <stack>
#include <fstream>
#include <sstream>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

class State
{
private:
	std::vector<sf::Texture> textures;                         
	sf::RenderWindow* window;

	bool quit;

public:
	State(sf::RenderWindow* window);
	virtual ~State();

	void checkForQuit();
	const bool& getQuit() const;

	virtual void endState() = 0;
	virtual void update(const float &dt) = 0;
	virtual void render(sf::RenderTarget *target = nullptr) = 0;
};

