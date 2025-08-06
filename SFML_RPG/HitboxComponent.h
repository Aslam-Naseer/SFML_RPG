#pragma once
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

class HitboxComponent
{
private:
	sf::Sprite& sprite;
	sf::RectangleShape hitbox;

	float offsetX;
	float offsetY;

public:
	HitboxComponent(sf::Sprite& sprite, float offset_x, float offset_y, float width, float height);
	~HitboxComponent();

	bool checkIntersect(sf::FloatRect frect);

	void update();
	void render(sf::RenderTarget& target);
};


