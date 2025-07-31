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
	void initVariables();

protected:
	sf::Texture* texture;
	sf::Sprite* sprite;

public:
	Entity();
	virtual ~Entity();

	void createSprite(sf::Texture* texture);

	virtual void setPosition(float x, float y);
	virtual void move(const float& dt, int dir_x, int dir_y);

	virtual void update(const float& dt);
	virtual void render(sf::RenderTarget* target);
};

