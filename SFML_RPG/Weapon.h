#pragma once

#include "Item.h"
#include "KeyTime.h"

class Weapon :
    public Item
{
protected:
	sf::Texture texture;
	sf::Sprite sprite;

	int minDamage;
	int maxDamage;
	int range;

	KeyTime timer;

public:
	Weapon(int val, int minDmg, int maxDmg, int rng);
	virtual ~Weapon();

	int getDamage() const;
	int getRange() const;
	bool isAttackReady() const;

	virtual Weapon* clone() = 0;
	virtual void update(const sf::Vector2f& mousePosView, const sf::Vector2f center, const sf::Vector2f velocity = { 0,0 }) = 0;
	virtual void render(sf::RenderTarget& target, sf::Shader* shader = nullptr) = 0;
};

