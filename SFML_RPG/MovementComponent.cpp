#include "MovementComponent.h"

MovementComponent::MovementComponent(sf::Sprite& sprite, float maxVelocity)
	: sprite(sprite), maxVelocity(maxVelocity), velocity(0.f, 0.f)
{
}

MovementComponent::~MovementComponent()
{
}

const sf::Vector2f& MovementComponent::getVelocity() const
{
	return velocity;
}

void MovementComponent::move(const float& dt, const int dir_x, const int dir_y)
{
	velocity.x = maxVelocity * dir_x;
	velocity.y = maxVelocity * dir_y;

	sprite.move(velocity * dt);
}
