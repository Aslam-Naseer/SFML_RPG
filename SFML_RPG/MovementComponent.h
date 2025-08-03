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


class MovementComponent
{
private:
	float maxVelocity;
	float acceleration;
	float deceleration;

	sf::Sprite& sprite;
	sf::Vector2f velocity;

	//float boundValue(float value, float min, float max) const;

public:
	MovementComponent(sf::Sprite& sprite, float maxVelocity, float acceleration, float deceleration);
	~MovementComponent();

	const sf::Vector2f& getVelocity() const;

	void move(const float& dt, const int dir_x, const int dir_y);
	void update(const float& dt);
};

