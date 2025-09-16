#pragma once

#include "Entity.h"
#include "Gui.h"

class Enemy :
    public Entity
{
protected:
    int expGain = 100;
    gui::ProgressBar* hpBar = nullptr;

    virtual void initAnimations() = 0;
    virtual void initHpBar(float maxHp, sf::Vector2f pos = {0,0});
public:
    Enemy(sf::Texture& texture);
    virtual ~Enemy();

    int getExpGain() const;

    virtual bool isDead() const;
    virtual void loseHp(int hp);

    virtual void updateAnimations(const float& dt) = 0;
};

