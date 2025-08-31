#pragma once

#include "Entity.h"

class Player :
    public Entity
{
private:
	bool attacking = false;
    bool facingRight = false;

    void initComponents();

public:

    Player(float x, float y, sf::Texture& texture);
    virtual ~Player();

	void updateAnimations(const float& dt);
    void update(const float& dt);
};

