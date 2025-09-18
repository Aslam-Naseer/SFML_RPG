#pragma once

#include "MovementComponent.h"
#include "AnimationComponent.h"
#include "HitboxComponent.h"
#include "AttributeComponent.h"
#include "SkillComponent.h"

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
	SkillComponent* skillComponent;

public:
	Entity(sf::Texture &texture);
    virtual ~Entity();

	void createMovementComponent(float maxVelocity, float acceleration, float deceleration);
	void createAnimationComponent(sf::Texture& texture);
	void createHitboxComponent(float offsetX, float offsetY, float width, float height);
	void createAttributeComponent(unsigned level);
	void createSkillComponent();

	virtual const sf::FloatRect getGlobalBounds() const;
	virtual const sf::FloatRect getNextPosBounds(const float& dt) const;
	virtual const sf::Vector2i getGridPosition(int gridSize) const;

	virtual const sf::Vector2f getCenter() const;
	virtual const sf::Vector2f getPosition() const;
	virtual const sf::Vector2f getVelocity() const;
	virtual void setPosition(float x, float y);

	virtual void stopMovement(bool dir_x = true, bool dir_y = true);
	virtual void move(const float& dt, int dir_x, int dir_y, bool stats = false);

	virtual void update(const float& dt, const sf::Vector2f& mousePosView = { -1,-1 }) = 0;
	virtual void render(sf::RenderTarget& target, sf::Shader* shader = nullptr, bool showHitbox = false) = 0;
};

