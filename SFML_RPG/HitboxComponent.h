#pragma once

class HitboxComponent
{
private:
	sf::Sprite& sprite;
	sf::RectangleShape hitbox;

	float offsetX;
	float offsetY;

public:
	HitboxComponent(sf::Sprite& sprite, float offset_x, float offset_y, float width, float height);
	~HitboxComponent();

	const sf::FloatRect getGlobalBounds() const;
	const sf::Vector2f getPosition() const;
	void setPosition(float x, float y);

	bool checkIntersect(sf::FloatRect frect);

	void update();
	void render(sf::RenderTarget& target);
};


