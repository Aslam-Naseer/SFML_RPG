#include "stdafx.h"
#include "Enemy.h"

void Enemy::initComponents(sf::Texture& texture)
{
	createMovementComponent(250.f, 1500.f, 700.f);
	createAnimationComponent(texture);
	createHitboxComponent(10.f, 2.f, 44.f, 60.f);
}

void Enemy::initAnimations()
{
	animationComponent->addAnimation("WALK_DOWN", 64, 64, 4, 0, .5f);
	animationComponent->addAnimation("WALK_LEFT", 64, 64, 4, 1, .5f);
	animationComponent->addAnimation("WALK_RIGHT", 64, 64, 4, 2, .5f);
	animationComponent->addAnimation("WALK_UP", 64, 64, 4, 3, .5f);
	animationComponent->addAnimation("IDLE", 64, 64, 9, 4, .5f);
}

Enemy::Enemy(float x, float y, sf::Texture& texture)
	: Entity(texture)
{
	sprite.setTextureRect({ { 0,0 }, {64,64} });

	initComponents(texture);
	setPosition(x, y);
	initAnimations();
}

Enemy::~Enemy()
{
}


void Enemy::updateAnimations(const float& dt)
{
	if (movementComponent->getState(MovementComponent::MovementState::Idle))
	{
		animationComponent->play("IDLE");
	}
	else if (movementComponent->getState(MovementComponent::MovementState::WalkUp))
	{
		animationComponent->play("WALK_UP");
	}
	else if (movementComponent->getState(MovementComponent::MovementState::WalkDown))
	{
		animationComponent->play("WALK_DOWN");
	}
	else if (movementComponent->getState(MovementComponent::MovementState::WalkLeft))
	{
		animationComponent->play("WALK_LEFT");
	}
	else if (movementComponent->getState(MovementComponent::MovementState::WalkRight))
	{
		animationComponent->play("WALK_RIGHT");
	}

	// Animate
	animationComponent->update(dt);

}

void Enemy::update(const float& dt, const sf::Vector2f& mousePosView)
{
	movementComponent->update(dt);

	updateAnimations(dt);
	hitboxComponent->update();
}

void Enemy::render(sf::RenderTarget& target, sf::Shader* shader, bool showHitbox)
{

	target.draw(sprite, shader);

	if (showHitbox)
		hitboxComponent->render(target);
}