#pragma once

#include "MovementComponent.h"
#include "AnimationComponent.h"

class Entity
{
private:
	void initVariables();

protected:
	sf::Sprite sprite;

	MovementComponent* movementComponent;
	AnimationComponent* animationComponent;

public:
	Entity(sf::Texture &texture);
	virtual ~Entity();

	void createMovementComponent(float maxVelocity, float acceleration, float deceleration);
	void createAnimationComponent(sf::Texture& texture);

	virtual void setPosition(float x, float y);
	virtual void move(const float& dt, int dir_x, int dir_y);

	virtual void update(const float& dt);
	virtual void render(sf::RenderTarget* target);
};

