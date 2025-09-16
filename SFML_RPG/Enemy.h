#pragma once

#include "Entity.h"
#include "Gui.h"
#include "EnemySpawner.h"

class Enemy :
    public Entity
{
protected:
    int expGain = 10;
    gui::ProgressBar* hpBar = nullptr;

    EnemySpawner& spawner;

    virtual void initAnimations() = 0;
    virtual void initHpBar(float maxHp, sf::Vector2f pos = {0,0});

    void calculateExpGain(int level);

public:
    Enemy(sf::Texture& texture, EnemySpawner& spawner);
    virtual ~Enemy();

    int getExpGain() const;
    EnemySpawner& getSpawner();

    virtual bool isDead() const;
    virtual void loseHp(int hp);

    virtual void updateAnimations(const float& dt) = 0;
};

