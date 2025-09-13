#pragma once

#include "Entity.h"

class Enemy :
    public Entity
{
private:
    virtual void initAnimations() = 0;

public:
    Enemy(sf::Texture& texture);
    virtual ~Enemy();

    virtual void updateAnimations(const float& dt) = 0;
};

