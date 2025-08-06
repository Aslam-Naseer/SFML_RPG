#pragma once
#include "Entity.h"

class Player :
    public Entity
{
private:

    void initComponents();

public:

    Player(float x, float y, sf::Texture& texture);
    virtual ~Player();

    void update(const float& dt);
};

