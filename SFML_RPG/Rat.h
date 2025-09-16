#pragma once

#include "Enemy.h"

class Rat :
    public Enemy
{
private:
    void initComponents(sf::Texture& texture);
	void initAnimations() override;

public:
    Rat(sf::Texture& texture, EnemySpawner& spawner);
    ~Rat();

    void updateAnimations(const float& dt) override;
    void update(const float& dt, const sf::Vector2f& mousePosView) override;
    void render(sf::RenderTarget& target, sf::Shader* shader, bool showHitbox = false) override;

};

