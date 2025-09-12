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


const bool MovementComponent::getState(const MovementState state) const
{
	switch (state)
	{
	case MovementState::Idle:
		return velocity.x == 0.f && velocity.y == 0.f;
	case MovementState::WalkLeft:
		return velocity.x < 0.f && std::abs(velocity.x) >= std::abs(velocity.y);
	case MovementState::WalkRight:
		return velocity.x > 0.f && std::abs(velocity.x) >= std::abs(velocity.y);
	case MovementState::WalkUp:
		return velocity.y < 0.f && std::abs(velocity.x) <= std::abs(velocity.y);
	case MovementState::WalkDown:
		return velocity.y > 0.f && std::abs(velocity.x) <= std::abs(velocity.y);
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
