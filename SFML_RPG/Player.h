#pragma once

#include "Entity.h"
#include "Sword.h"
#include "Bow.h"
#include "Inventory.h"
#include "KeyTime.h"

class Player :
    public Entity
{
private:
	bool attacking = false;
    bool facingRight = false;

    Inventory inventory;
    Sword sword;

    KeyTime timer;
    std::string stats;

    void initComponents(sf::Texture& texture);
    void initAnimations();

public:
    Player(float x, float y, sf::Texture& texture);
    virtual ~Player();

    const AttributeComponent* getAttributeComponent() const;
	const std::string getStats() const;
    const Weapon* getWeapon() const;
    bool isAttacking() const;

    void gainHp(int hp);
    void loseHp(int hp);
    void gainExp(int exp);
    void loseExp(int exp);

    void refreshStats();
    void attack();

	void updateAnimations(const float& dt);
    void update(const float& dt, const sf::Vector2f& mousePosView) override;
    void render(sf::RenderTarget& target, sf::Shader* shader = nullptr, bool showHitbox = false) override;
};

