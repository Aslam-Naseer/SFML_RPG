#pragma once

#include "Entity.h"

class Enemy :
    public Entity
{
private:
    bool attacking = false;
    bool facingRight = false;

    void initComponents(sf::Texture& texture);
    void initAnimations();

public:
    Enemy(float x, float y, sf::Texture& texture);
    virtual ~Enemy();

    void updateAnimations(const float& dt);
    void update(const float& dt, const sf::Vector2f& mousePosView = { -1,-1 }) override;
    void render(sf::RenderTarget& target, sf::Shader* shader = nullptr, bool showHitbox = false) override;
};

