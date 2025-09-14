#pragma once

#include "MeleeWeapon.h"

class Sword :
    public MeleeWeapon
{
private:

public:
    Sword();
	virtual ~Sword();

    Sword* clone() override;

    void update(const sf::Vector2f& mousePosView, const sf::Vector2f center, const sf::Vector2f velocity) override;
    void render(sf::RenderTarget& target, sf::Shader* shader = nullptr) override;
};

