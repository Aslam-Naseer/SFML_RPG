#pragma once

#include "Item.h"

class MeleeWeapon :
    public Item
{
protected:
	sf::Texture texture;
	sf::Sprite sprite;

	int minDamage = 1;
	int maxDamage = 10;

public:
    MeleeWeapon(int val);
    virtual ~MeleeWeapon();

	virtual MeleeWeapon* clone() = 0;

	virtual void update(const sf::Vector2f& mousePosView, const sf::Vector2f center, const sf::Vector2f velocity = { 0,0 }) = 0;
	virtual void render(sf::RenderTarget& target, sf::Shader* shader = nullptr) = 0;
};

