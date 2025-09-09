#include "stdafx.h"
#include "Player.h"

// Constructors and Destructors

void Player::initComponents()
{
}

Player::Player(float x, float y, sf::Texture& texture)
	: Entity(texture)
{
	//initComponents();
	createMovementComponent(700.f, 3000.f, 1000.f);
	createAnimationComponent(texture);
	createHitboxComponent(95, 55, 80, 135);
	createAttributeComponent(1);

	setPosition(x, y);

	animationComponent->addAnimation("IDLE", 192, 192, 14, 0, .5f);
	animationComponent->addAnimation("WALK", 192, 192, 11, 1, .7f);
	animationComponent->addAnimation("ATTACK", 192 * 2, 192, 14, 2, .7f);

}

Player::~Player()
{
}


const AttributeComponent* Player::getAttributeComponent() const
{
	return attributeComponent ? attributeComponent : nullptr;
}

void Player::gainHp(int hp)
{
	attributeComponent->hp += hp;

	if (attributeComponent->hp > attributeComponent->hpMax)
		attributeComponent->hp = attributeComponent->hpMax;
}

void Player::loseHp(int hp)
{
	attributeComponent->hp -= hp;

	if (attributeComponent->hp < 0)
		attributeComponent->hp = 0;
}

void Player::gainExp(unsigned exp)
{
	attributeComponent->gainExp(exp);
}

void Player::loseExp(unsigned exp)
{
	attributeComponent->exp -= exp;

	if (attributeComponent->exp < 0)
		attributeComponent->exp = 0;
}

void Player::updateAnimations(const float& dt)
{
	

	// Play animations
	if (attacking)
		animationComponent->play("ATTACK", true);

	if (movementComponent->getState(MovementComponent::movement_state::IDLE))
	{
		animationComponent->play("IDLE");
	}
	else if (movementComponent->getState(MovementComponent::movement_state::WALK_LEFT))
	{
		animationComponent->play("WALK");
	}
	else if (movementComponent->getState(MovementComponent::movement_state::WALK_RIGHT))
	{
		animationComponent->play("WALK");
	}
	else if (movementComponent->getState(MovementComponent::movement_state::WALK_UP))
	{
		animationComponent->play("WALK");
	}
	else if (movementComponent->getState(MovementComponent::movement_state::WALK_DOWN))
	{
		animationComponent->play("WALK");
	}


	
	// Animate
	animationComponent->update(dt);
	if (!animationComponent->isPriority("ATTACK"))
		attacking = false;

	// Hitbox update
	if (facingRight)
	{
		sprite.setScale({ -1.f, 1.f });

		if (attacking)
			sprite.setOrigin({ 258.f + 96.f, 0.f });
		else
			sprite.setOrigin({ 258, 0.f });
	}
	else
	{
		sprite.setScale({ 1.f, 1.f });

		if (attacking)
			sprite.setOrigin({ 96.f, 0.f });
		else
			sprite.setOrigin({ 0.f, 0.f });
	}

	if (movementComponent->getVelocity().x > 0.f) // Moving right
	{
		facingRight = true;
	}
	else if (movementComponent->getVelocity().x < 0.f) // Moving left
	{
		facingRight = false;
	}
}

void Player::update(const float& dt)
{
	movementComponent->update(dt);

	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
	{
		attacking = true;
	}

	updateAnimations(dt);
	hitboxComponent->update();
}

void Player::render(sf::RenderTarget& target)
{
	target.draw(sprite);
	hitboxComponent->render(target);
}