#include "stdafx.h"
#include "Sword.h"

Sword::Sword()
{
	if (!texture.loadFromFile("Resources/Sprites/Player/sword.png"))
	{
		std::cout << "ERROR::SWORD::CONSTRUCTOR::FAILED_TO_LOAD_TEXTURE" << std::endl;
		return;
	}

	sprite.setTextureRect({ {0,0}, {static_cast<int>(texture.getSize().x), static_cast<int>(texture.getSize().y)} });
	sprite.setOrigin({ texture.getSize().x / 2.f,  static_cast<float>(texture.getSize().y) });
}

Sword::~Sword()
{
}

void Sword::update(const sf::Vector2f& mousePosView, const sf::Vector2f center, const sf::Vector2f velocity)
{
	sprite.setPosition({center.x, center.y + 10.f});

	float dx = mousePosView.x - center.x;
	float dy = mousePosView.y - center.y;

/*	if (velocity.x > 0)
		dx = std::abs(dx);  
	else if (velocity.x < 0)
		dx = std::abs(dx) * -1;

	if (velocity.y > 0)
		dy = std::abs(dy);  
	else if (velocity.y < 0)
		dy = std::abs(dy) * -1;  */  

	const float PI = 3.14159265f;
	float deg = atan2(dy, dx) * 180 / PI;

	sprite.setRotation(sf::degrees(deg + 90));
}

void Sword::render(sf::RenderTarget& target, sf::Shader* shader)
{
	target.draw(sprite, shader);
}
