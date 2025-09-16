#pragma once

#include "Weapon.h"

class RangedWeapon :
    public Weapon
{
protected:
    void generateStats();

public:
    RangedWeapon(unsigned lvl);
    virtual ~RangedWeapon();

    virtual RangedWeapon* clone() = 0;
    virtual void generateRandom(unsigned levelMin, unsigned levelMax);

    virtual void update(const sf::Vector2f& mousePosView, const sf::Vector2f center, const sf::Vector2f velocity = { 0,0 }) = 0;
    virtual void render(sf::RenderTarget& target, sf::Shader* shader = nullptr) = 0;
};

