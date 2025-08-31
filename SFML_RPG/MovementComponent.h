#pragma once

class MovementComponent
{
private:
	float maxVelocity;
	float acceleration;
	float deceleration;

	sf::Sprite& sprite;
	sf::Vector2f velocity;

public:
	enum class movement_state { IDLE, WALK_LEFT, WALK_RIGHT, WALK_UP, WALK_DOWN};

	MovementComponent(sf::Sprite& sprite, float maxVelocity, float acceleration, float deceleration);
	~MovementComponent();

	const sf::Vector2f& getVelocity() const;

	const bool getState(const movement_state state) const;

	void move(const float& dt, const int dir_x, const int dir_y);
	void update(const float& dt);
};

