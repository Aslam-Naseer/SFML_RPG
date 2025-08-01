#include "MovementComponent.h"

MovementComponent::MovementComponent(float maxVelocity):
	maxVelocity(maxVelocity)
{
}

MovementComponent::~MovementComponent()
{
}

const sf::Vector2f& MovementComponent::getVelocity() const
{
	return velocity;
}

void MovementComponent::move(sf::Sprite* sprite, const float& dt, const int dir_x, const int dir_y)
{
	velocity.x = maxVelocity * dir_x;
	velocity.y = maxVelocity * dir_y;

	sprite->move(velocity * dt);
}
