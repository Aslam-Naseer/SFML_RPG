#pragma once

#include "MovementComponent.h"
#include "AnimationComponent.h"
#include "HitboxComponent.h"
#include "AttributeComponent.h"

class Entity
{
private:
	void initVariables();

protected:
	sf::Sprite sprite;

	MovementComponent* movementComponent;
	AnimationComponent* animationComponent;
	HitboxComponent* hitboxComponent;
	AttributeComponent* attributeComponent;

public:
	Entity(sf::Texture &texture);
    virtual ~Entity();

	void createMovementComponent(float maxVelocity, float acceleration, float deceleration);
	void createAnimationComponent(sf::Texture& texture);
	void createHitboxComponent(float offsetX, float offsetY, float width, float height);
	void createAttributeComponent(unsigned level);

	virtual const sf::FloatRect getGlobalBounds() const;
	virtual const sf::FloatRect getNextPosBounds(const float& dt) const;
	virtual const sf::Vector2i getGridPosition(int gridSize) const;
	virtual const sf::Vector2f getCenter() const;
	virtual const sf::Vector2f getPosition() const;
	virtual void setPosition(float x, float y);

	virtual void stopMovement(bool dir_x = true, bool dir_y = true);
	virtual void move(const float& dt, int dir_x, int dir_y);

	virtual void update(const float& dt) = 0;
	virtual void render(sf::RenderTarget& target, sf::Shader* shader = nullptr, bool showHitbox = false) = 0;
};

