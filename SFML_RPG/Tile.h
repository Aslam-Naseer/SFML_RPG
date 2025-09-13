#pragma once

class Tile
{
public:
	enum class Type : short {
		Default = 0,
		Damaging,
		Floating
	};

protected:
	sf::Sprite shape;
	bool collision;
	Type type;

public:
	Tile(float x, float y, const sf::Texture& tileSheet,
		const sf::IntRect& textureRect, Type type = Type::Default, bool collision = false);
	virtual ~Tile();

	std::string toString();
	void setPosition(float x, float y);

	bool intersects(const sf::FloatRect bounds) const;
	
	virtual void update();
	virtual void render(sf::RenderTarget& target, sf::Shader* shader = nullptr);

	friend class TileMap;
};

