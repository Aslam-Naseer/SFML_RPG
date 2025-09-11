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
	createMovementComponent(400.f, 1500.f, 700.f);
	createAnimationComponent(texture);
	createHitboxComponent(10.f, 2.f, 44.f, 60.f);
	createAttributeComponent(1);

	setPosition(x, y);

	animationComponent->addAnimation("WALK_DOWN", 64, 64, 4, 0, .5f);
	animationComponent->addAnimation("WALK_LEFT", 64, 64, 4, 1, .5f);
	animationComponent->addAnimation("WALK_RIGHT", 64, 64, 4, 2, .5f);
	animationComponent->addAnimation("WALK_UP", 64, 64, 4, 3, .5f);
	animationComponent->addAnimation("IDLE", 64, 64, 9, 4, .5f);
	//animationComponent->addAnimation("ATTACK", 192 * 2, 192, 14, 2, .7f);

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

void Player::gainExp(int exp)
{
	attributeComponent->gainExp(exp);
}

void Player::loseExp(int exp)
{
	attributeComponent->exp -= exp;

	if (attributeComponent->exp < 0)
		attributeComponent->exp = 0;
}

void Player::updateAnimations(const float& dt)
{
	

	// Play animations
	//if (attacking)
	//	animationComponent->play("ATTACK", true);

	if (movementComponent->getState(MovementComponent::movement_state::IDLE))
	{
		animationComponent->play("IDLE");
	}
	else if (movementComponent->getState(MovementComponent::movement_state::WALK_UP))
	{
		animationComponent->play("WALK_UP");
	}
	else if (movementComponent->getState(MovementComponent::movement_state::WALK_DOWN))
	{
		animationComponent->play("WALK_DOWN");
	}
	else if (movementComponent->getState(MovementComponent::movement_state::WALK_LEFT))
	{
		animationComponent->play("WALK_LEFT");
	}
	else if (movementComponent->getState(MovementComponent::movement_state::WALK_RIGHT))
	{
		animationComponent->play("WALK_RIGHT");
	}


	
	// Animate
	animationComponent->update(dt);
	if (!animationComponent->isPriority("ATTACK"))
		attacking = false;

}

void Player::update(const float& dt)
{
	movementComponent->update(dt);

	//if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
	//{
	//	attacking = true;
	//}

	updateAnimations(dt);
	hitboxComponent->update();
}

void Player::render(sf::RenderTarget& target, sf::Shader* shader, bool showHitbox)
{
	target.draw(sprite, shader);

	if(showHitbox)
		hitboxComponent->render(target);
}