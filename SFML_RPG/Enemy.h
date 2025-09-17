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
    KeyTime flashTimer;

    bool damaged = false;

    float trackRange = 700.f;
    float attackRange = 50.f;

    virtual void initAnimations() = 0;
    virtual void initHpBar(float maxHp, sf::Vector2f pos = {0,0});

    void calculateExpGain(int level);
    void updateDamageFlash();

public:
    Enemy(sf::Texture& texture, EnemySpawner& spawner);
    virtual ~Enemy();

    int getExpGain() const;
    float getTrackRange() const;
    float getAttackRange() const;
    EnemySpawner& getSpawner();

    virtual bool isDead() const;
    virtual void loseHp(int hp);
    virtual void attack(sf::Vector2f target) const;

    virtual void updateAnimations(const float& dt) = 0;
};

