#pragma once

#include "Entity.h"

class Enemy :
    public Entity
{
private:
    int expGain = 100;

    virtual void initAnimations() = 0;

public:
    Enemy(sf::Texture& texture);
    virtual ~Enemy();

    int getExpGain() const;

    virtual bool isDead() const;
    virtual void loseHp(int hp);

    virtual void updateAnimations(const float& dt) = 0;
};

