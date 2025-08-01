#include "Player.h"

// Constructors and Destructors

void Player::initComponents()
{
	createMovementComponent(500.f);
}

Player::Player(float x, float y, sf::Texture *texture)
{
	initComponents();

	createSprite(texture);
	setPosition(x, y);
}

Player::~Player()
{
}