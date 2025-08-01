#include "Entity.h"

// Constructors and Destructors

void Entity::initVariables()
{
	texture = NULL;
	sprite = NULL;
	movementComponent = NULL;
}

Entity::Entity()
{
	initVariables();
}

Entity::~Entity()
{
	delete sprite;
	delete movementComponent;
}

void Entity::createSprite(sf::Texture* texture)
{
	this->texture = texture;
	this->sprite = new sf::Sprite(*texture);
}

void Entity::createMovementComponent(float maxVelocity)
{
	movementComponent = new MovementComponent(maxVelocity);
}

// Functions

void Entity::setPosition(float x, float y)
{
	if(!sprite)
		return;
	sprite->setPosition({ x, y });
}

void Entity::move(const float& dt, int dir_x, int dir_y)
{
	if (!sprite || !movementComponent)
		return;

	movementComponent->move(sprite, dt, dir_x, dir_y);
}

void Entity::update(const float& dt)
{
	
}

void Entity::render(sf::RenderTarget* target)
{
	if (!sprite)
		return;

	target->draw(*sprite);
}
