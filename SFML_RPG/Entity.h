#pragma once

#include "MovementComponent.h"

class Entity
{
private:
	void initVariables();

protected:
	sf::Sprite sprite;

	MovementComponent* movementComponent;

public:
	Entity(sf::Texture &texture);
	virtual ~Entity();

	void createMovementComponent(float maxVelocity);

	virtual void setPosition(float x, float y);
	virtual void move(const float& dt, int dir_x, int dir_y);

	virtual void update(const float& dt);
	virtual void render(sf::RenderTarget* target);
};

