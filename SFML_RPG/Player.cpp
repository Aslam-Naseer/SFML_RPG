#include "Player.h"

// Constructors and Destructors

void Player::initComponents()
{
	createMovementComponent(500.f);
}

Player::Player(float x, float y, sf::Texture& texture)
	: Entity(texture)
{
	initComponents();

	setPosition(x, y);
}

Player::~Player()
{
}