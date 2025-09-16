#pragma once

#include "Item.h"
#include "KeyTime.h"

class Weapon :
    public Item
{
protected:
	sf::Texture texture;
	sf::Sprite sprite;

	int minDamage = 1;
	int maxDamage = 5;
	int range = 50;

	KeyTime timer;

	virtual void generateStats() = 0;

public:
	Weapon(unsigned lvl);
	virtual ~Weapon();

	int getDamage() const;
	int getRange() const;
	bool isAttackReady() const;

	virtual Weapon* clone() = 0;
	virtual void generateRandom(unsigned levelMin, unsigned levelMax) = 0;

	virtual void update(const sf::Vector2f& mousePosView, const sf::Vector2f center, const sf::Vector2f velocity = { 0,0 }) = 0;
	virtual void render(sf::RenderTarget& target, sf::Shader* shader = nullptr) = 0;
};

