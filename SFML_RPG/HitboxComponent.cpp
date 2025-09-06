#include "stdafx.h"
#include "HitboxComponent.h"

HitboxComponent::HitboxComponent(sf::Sprite& sprite, float offset_x, float offset_y, float width, float height)
	: sprite(sprite), offsetX(offset_x), offsetY(offset_y)
{
	hitbox.setPosition({ sprite.getPosition().x + offset_x, sprite.getPosition().y + offset_y });
	hitbox.setSize({ width, height });

	hitbox.setFillColor(sf::Color::Transparent);
	hitbox.setOutlineThickness(1.f);
	hitbox.setOutlineColor(sf::Color::Green);
}

HitboxComponent::~HitboxComponent()
{
}

const sf::FloatRect HitboxComponent::getGlobalBounds() const
{
	return hitbox.getGlobalBounds();
}

const sf::Vector2f HitboxComponent::getPosition() const
{
	return hitbox.getPosition();
}

void HitboxComponent::setPosition(float x, float y)
{
	hitbox.setPosition({ x,y });
	sprite.setPosition({ x - offsetX, y - offsetY });
}

bool HitboxComponent::checkIntersect(sf::FloatRect frect)
{
	// Write this later
	return false;
}

void HitboxComponent::update()
{
	hitbox.setPosition({ sprite.getPosition().x + offsetX, sprite.getPosition().y + offsetY });
}

void HitboxComponent::render(sf::RenderTarget& target)
{
	target.draw(hitbox);
}
