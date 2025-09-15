#pragma once

#include "RangedWeapon.h"

class Bow :
    public RangedWeapon
{
private:

public:
    Bow();
    virtual ~Bow();

    Bow* clone() override;

    void update(const sf::Vector2f& mousePosView, const sf::Vector2f center, const sf::Vector2f velocity) override;
    void render(sf::RenderTarget& target, sf::Shader* shader = nullptr) override;
};

