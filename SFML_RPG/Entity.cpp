#include "Entity.h"

// Constructors and Destructors

void Entity::initVariables()
{
	movementComponent = NULL;
	animationComponent = NULL;
	hitboxComponent = NULL;
}


Entity::Entity(sf::Texture& texture) :
	sprite(texture)
{
	initVariables();
}

Entity::~Entity()
{
	delete movementComponent;
	delete animationComponent;
	delete hitboxComponent;
}

void Entity::createMovementComponent(float maxVelocity, float acceleration, float deceleration)
{
	movementComponent = new MovementComponent(sprite, maxVelocity, acceleration, deceleration);
}

void Entity::createAnimationComponent(sf::Texture& texture)
{
	animationComponent = new AnimationComponent(sprite, texture);
}

void Entity::createHitboxComponent(float offsetX, float offsetY, float width, float height)
{
	hitboxComponent = new HitboxComponent(sprite, offsetX, offsetY, width, height);
}

// Functions

void Entity::setPosition(float x, float y)
{
	sprite.setPosition({ x, y });
}

void Entity::move(const float& dt, int dir_x, int dir_y)
{
	if (!movementComponent)
		return;

	movementComponent->move(dt, dir_x, dir_y);
}

void Entity::update(const float& dt)
{
	if (movementComponent != NULL)
		movementComponent->update(dt);

	if (animationComponent != NULL)
		animationComponent->update(dt);
}

void Entity::render(sf::RenderTarget& target)
{
	target.draw(sprite);

	if (hitboxComponent != NULL)
		hitboxComponent->render(target);
}
