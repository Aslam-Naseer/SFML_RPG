#include "Player.h"

// Constructors and Destructors

Player::Player(float x, float y, sf::Texture *texture)
{
	createSprite(texture);
	setPosition(x, y);
}

Player::~Player()
{
}