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

class Entity
{
private:
	float speed;

protected:
	sf::RectangleShape shape;

public:
	Entity();
	virtual ~Entity();

	void move(const float& dt, int dir_x, int dir_y);

	void update(const float& dt);
	void render(sf::RenderTarget* target);
};

