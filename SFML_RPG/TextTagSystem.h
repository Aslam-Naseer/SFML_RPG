#pragma once

class TextTagSystem
{
public:
	enum class TagType {
		DefaultTag,
		NegativeTag,
		PositiveTag,
		ExperienceTag
	};

private:
	class TextTag
	{
	public:
		sf::Text text;
		sf::Vector2f direction;
		float lifetime;
		float speed;

		TextTag(sf::Font& font, std::string str, sf::Color color, unsigned charSize,
			sf::Vector2f position, sf::Vector2f direction, float lifetime, float speed);
		
		void update(const float& dt);
		void render(sf::RenderTarget& target);
	};

	sf::Font font;
	std::vector<TextTag> textTags;
	void createTextTag(TagType type, float x, float y, std::string str);

public:
	TextTagSystem(sf::Font& font);
	virtual ~TextTagSystem();

	template<typename T>
	void addTextTag(TagType type, float x, float y, T val, std::string prefix = "", std::string postfix = "");

	void update(const float& dt);
	void render(sf::RenderTarget& target);
};

template<typename T>
inline void TextTagSystem::addTextTag(TagType type, float x, float y, T val, std::string prefix, std::string postfix)
{
	std::ostringstream ss;
	ss << prefix << " " << val << " " << postfix;
	createTextTag(type, x, y, ss.str());
}
