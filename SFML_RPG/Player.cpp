#include "stdafx.h"
#include "Player.h"

// Constructors and Destructors

void Player::initComponents(sf::Texture& texture)
{
	createMovementComponent(400.f, 1500.f, 700.f);
	createAnimationComponent(texture);
	createHitboxComponent(10.f, 2.f, 44.f, 60.f);
	createAttributeComponent(1);
	createSkillComponent();
}

void Player::initAnimations()
{
	animationComponent->addAnimation("WALK_DOWN", 64, 64, 4, 0, .5f);
	animationComponent->addAnimation("WALK_LEFT", 64, 64, 4, 1, .5f);
	animationComponent->addAnimation("WALK_RIGHT", 64, 64, 4, 2, .5f);
	animationComponent->addAnimation("WALK_UP", 64, 64, 4, 3, .5f);
	animationComponent->addAnimation("IDLE", 64, 64, 9, 4, .5f);
	//animationComponent->addAnimation("ATTACK", 192 * 2, 192, 14, 2, .7f);
}

Player::Player(float x, float y, sf::Texture& texture)
	: Entity(texture), inventory(10)
{
	sprite.setTextureRect({ { 0,0 }, {64,64} });
	setPosition(x, y);

	initComponents(texture);
	initAnimations();

	refreshStats();
}

Player::~Player()
{
}


const AttributeComponent* Player::getAttributeComponent() const
{
	return attributeComponent ? attributeComponent : nullptr;
}

const std::string Player::getStats() const
{
	return stats;
}

const Weapon* Player::getWeapon() const
{

	return &sword;
}

bool Player::isAttacking() const
{
	return attacking;
}

void Player::gainHp(int hp)
{
	attributeComponent->gainHp(hp);
	refreshStats();
}

void Player::loseHp(int hp)
{
	attributeComponent->loseHp(hp);
	refreshStats();
}

void Player::gainExp(int exp)
{
	attributeComponent->gainExp(exp);
	refreshStats();
}

void Player::loseExp(int exp)
{
	attributeComponent->loseExp(exp);
	refreshStats();
}


void Player::refreshStats()
{
	std::ostringstream ss;
	const AttributeComponent* ac = attributeComponent;
	const Weapon* w = &sword;

	ss << "Level: " << ac->level << "\n"
		<< "Exp: " << ac->exp << "\n"
		<< "Exp next: " << ac->expNext << "\n"
		<<"\n"
		<< "Weapon Level: " << w->getLevel() << "\n"
		<< "Weapon Type: " << "Sword" << "\n"
		<< "Weapon Value: " << w->getValue() << " G\n"
		<< "Weapon Range: " << w->getRange() << "\n"
		<< "Weapon Damage : " << "[ " << w->getDamageMin() << " - " << w->getDamageMax() << " ]\n";

	stats = ss.str();
}

void Player::attack()
{
	attacking = true;
}


void Player::updateAnimations(const float& dt)
{

	// Play animations
	//if (attacking)
	//	animationComponent->play("ATTACK", true);

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

void Player::update(const float& dt, const sf::Vector2f& mousePosView)
{

	if (attacking && timer.consume())
		attacking = false;

	movementComponent->update(dt);
	updateAnimations(dt);
	sword.update(mousePosView, getCenter(), movementComponent->getVelocity());
	hitboxComponent->update();
}

void Player::render(sf::RenderTarget& target, sf::Shader* shader, bool showHitbox)
{
	if (animationComponent->isPlaying("WALK_UP"))
	{
		sword.render(target, shader);
		target.draw(sprite, shader);
	}
	else
	{
		target.draw(sprite, shader);
		sword.render(target, shader);
	}


	if(showHitbox)
		hitboxComponent->render(target);
}