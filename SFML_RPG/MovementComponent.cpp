#include "stdafx.h"
#include "MovementComponent.h"

MovementComponent::MovementComponent(sf::Sprite& sprite, float maxVelocity, float acceleration, float deceleration)
	: maxVelocity(maxVelocity), acceleration(acceleration), deceleration(deceleration), 
		velocity(0.f, 0.f), sprite(sprite)
{
}

MovementComponent::~MovementComponent()
{
}

const sf::Vector2f& MovementComponent::getVelocity() const
{
	return velocity;
}


const bool MovementComponent::getState(const movement_state state) const
{
	switch (state)
	{
	case movement_state::IDLE:
		return velocity.x == 0.f && velocity.y == 0.f;
	case movement_state::WALK_LEFT:
		return velocity.x < 0.f;
	case movement_state::WALK_RIGHT:
		return velocity.x > 0.f;
	case movement_state::WALK_UP:
		return velocity.y < 0.f;
	case movement_state::WALK_DOWN:
		return velocity.y > 0.f;
	default:
		return false;
	}
}

void MovementComponent::stopMovement(bool dir_x, bool dir_y)
{
	if (dir_x)
		velocity.x = 0;

	if (dir_y)
		velocity.y = 0;
}

void MovementComponent::move(const float& dt, const int dir_x, const int dir_y)
{
	// Accelerate

	velocity.x += acceleration * dir_x * dt;
	velocity.y += acceleration * dir_y * dt;

	velocity.x = std::clamp(velocity.x, -maxVelocity, maxVelocity);
	velocity.y = std::clamp(velocity.y, -maxVelocity, maxVelocity);
}

void MovementComponent::update(const float& dt)
{
	// Decelerate
	
	velocity.x -= deceleration * (velocity.x > 0 ? 1 : -1) * dt;
	velocity.y -= deceleration * (velocity.y > 0 ? 1 : -1) * dt;

	if (std::abs(velocity.x) <= deceleration * dt)
		velocity.x = 0.f;
	if (std::abs(velocity.y) <= deceleration * dt)
		velocity.y = 0.f;

	// Update

	sprite.move(velocity * dt);
}
