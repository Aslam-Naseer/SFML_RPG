#pragma once

#include "Entity.h"
#include "Sword.h"
#include "Bow.h"


class Player :
    public Entity
{
private:
	bool attacking = false;
    bool facingRight = false;

    Sword sword;

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
    void update(const float& dt, const sf::Vector2f& mousePosView);
    void render(sf::RenderTarget& target, sf::Shader* shader = nullptr, bool showHitbox = false);
};

