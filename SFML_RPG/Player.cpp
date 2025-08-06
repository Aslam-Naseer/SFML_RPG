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
	animationComponent->addAnimation("WALK", 192, 192, 11, 1, .7f);

}

Player::~Player()
{
}

void Player::update(const float& dt)
{
	movementComponent->update(dt);

	if (movementComponent->getState(MovementComponent::movement_state::WALK_LEFT))
		animationComponent->play("WALK");
	else
		animationComponent->play("IDLE");

	animationComponent->update(dt);
}