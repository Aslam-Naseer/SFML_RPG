#include "stdafx.h"
#include "Rat.h"


void Rat::initComponents(sf::Texture& texture)
{
	createMovementComponent(120.f, 1200.f, 400.f);
	createAnimationComponent(texture);
	createHitboxComponent(13.f, 39.f, 30.f, 30.f);
	createAttributeComponent(5);
}

void Rat::initAnimations()
{
	animationComponent->addAnimation("WALK_DOWN", 60, 64, 4, 1, .5f);
	animationComponent->addAnimation("WALK_LEFT", 60, 64, 4, 2, .5f);
	animationComponent->addAnimation("WALK_RIGHT", 60, 64, 4, 3, .5f);
	animationComponent->addAnimation("WALK_UP", 60, 64, 4, 4, .5f);
	animationComponent->addAnimation("IDLE", 60, 64, 4, 0, .5f);
}


Rat::Rat(sf::Texture& texture, EnemySpawner& spawner):
	Enemy(texture, spawner)
{
	auto [x, y] = spawner.getPosition();

	sprite.setTextureRect({ {0, 0}, {64, 64} });
	setPosition(x, y);

	initComponents(texture);
	initAnimations();
	initHpBar(static_cast<float>(attributeComponent->hpMax));

	calculateExpGain(attributeComponent->level);
}

Rat::~Rat()
{
}

void Rat::updateAnimations(const float& dt)
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

void Rat::update(const float& dt, const sf::Vector2f& mousePosView)
{
	movementComponent->update(dt);
	updateAnimations(dt);
	updateDamageFlash();
	hitboxComponent->update();

	hpBar->setPosition({ sprite.getPosition().x, sprite.getPosition().y + 20.f});

}

void Rat::render(sf::RenderTarget& target, sf::Shader* shader, bool showHitbox)
{

	target.draw(sprite, shader);
	hpBar->render(target);

	if (showHitbox)
		hitboxComponent->render(target);
}