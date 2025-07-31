#include "Entity.h"

// Constructors and Destructors

void Entity::initVariables()
{
	speed = 350.f; // Default speed
	texture = NULL;
	sprite = NULL;
}

Entity::Entity()
{
	initVariables();
}

Entity::~Entity()
{
	delete sprite;
}

void Entity::createSprite(sf::Texture* texture)
{
	this->texture = texture;
	this->sprite = new sf::Sprite(*texture);
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
	if (!sprite)
		return;

	sprite->move({ dir_x * speed * dt, dir_y * speed * dt });
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
