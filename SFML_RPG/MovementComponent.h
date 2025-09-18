#pragma once

class MovementComponent
{
public:
	enum class MovementState {
		Idle,
		WalkLeft,
		WalkRight,
		WalkUp,
		WalkDown
	};

private:
	float maxVelocity;
	float acceleration;
	float deceleration;

	sf::Sprite& sprite;
	sf::Vector2f velocity;

public:
	MovementComponent(sf::Sprite& sprite, float maxVelocity, float acceleration, float deceleration);
	~MovementComponent();

	const sf::Vector2f& getVelocity() const;
	const bool getState(const MovementState state) const;

	void stopMovement(bool dir_x = true, bool dir_y = true);
	void move(const float& dt, const int dir_x, const int dir_y, bool stats = false);
	void update(const float& dt);
};

