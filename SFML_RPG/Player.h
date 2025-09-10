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

    const AttributeComponent* getAttributeComponent() const;

    void gainHp(int hp);
    void loseHp(int hp);
    void gainExp(int exp);
    void loseExp(int exp);

	void updateAnimations(const float& dt);
    void update(const float& dt);
    void render(sf::RenderTarget& target, bool showHitbox = false);
};

