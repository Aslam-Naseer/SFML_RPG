#include "stdafx.h"
#include "Entity.h"

// Constructors and Destructors

void Entity::initVariables()
{
	movementComponent = NULL;
	animationComponent = NULL;
	hitboxComponent = NULL;
	attributeComponent = NULL;
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
	delete attributeComponent;
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

void Entity::createAttributeComponent(unsigned level)
{
	attributeComponent = new AttributeComponent(level);
}

// Functions

const sf::FloatRect Entity::getGlobalBounds() const
{
	if (hitboxComponent)
		return hitboxComponent->getGlobalBounds();

	return sprite.getGlobalBounds();
}

const sf::FloatRect Entity::getNextPosBounds(const float& dt) const
{
	if(hitboxComponent && movementComponent)
		return hitboxComponent->getNextPosition(movementComponent->getVelocity() * dt);

	return sf::FloatRect({{-1,-1}, {-1,-1}});
}

const sf::Vector2i Entity::getGridPosition(int gridSize) const
{
	return sf::Vector2i({
			static_cast<int>(getPosition().x) / gridSize,
			static_cast<int>(getPosition().y) / gridSize
		});
}

const sf::Vector2f Entity::getPosition() const
{
	if (hitboxComponent)
		return hitboxComponent->getPosition();

	return sprite.getPosition();
}

void Entity::setPosition(float x, float y)
{
	if (hitboxComponent)
		hitboxComponent->setPosition(x, y);
	else
		sprite.setPosition({ x, y });
}

void Entity::stopMovement(bool dir_x, bool dir_y)
{
	if (movementComponent)
		movementComponent->stopMovement(dir_x, dir_y);
}

void Entity::move(const float& dt, int dir_x, int dir_y)
{
	if (!movementComponent)
		return;

	movementComponent->move(dt, dir_x, dir_y);
}
