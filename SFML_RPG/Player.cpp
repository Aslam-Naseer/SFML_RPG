#include "Player.h"

// Constructors and Destructors

void Player::initComponents()
{
}

Player::Player(float x, float y, sf::Texture& texture)
	: Entity(texture)
{
	//initComponents();
	createMovementComponent(700.f, 25.f, 5.f);
	createAnimationComponent(texture);

	setPosition(x, y);
	animationComponent->addAnimation("IDLE", 192, 192, 14, 0, .5f);
	animationComponent->play("IDLE");  


}

Player::~Player()
{
}