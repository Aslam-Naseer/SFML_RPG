#pragma once

enum class ButtonState
{
	IDLE = 0,
	HOVER,
	ACTIVE
};

namespace gui
{
	class Button
	{
	private:
		sf::RectangleShape shape;
		sf::Font& font;
		sf::Text text;

		sf::Color idleColor;
		sf::Color hoverColor;
		sf::Color activeColor;

		sf::Color textIdleColor;
		sf::Color textHoverColor;
		sf::Color textActiveColor;

		sf::Color outlineIdleColor;
		sf::Color outlineHoverColor;
		sf::Color outlineActiveColor;

		ButtonState buttonState;
		short unsigned id = -1;

	public:

		Button(float x, float y, float width, float height,
			const std::string& text, sf::Font& font, unsigned int charSize,
			sf::Color text_idle_color, sf::Color text_hover_color, sf::Color text_active_color,
			sf::Color idle_color, sf::Color hover_color, sf::Color active_color,
			sf::Color outline_idle_color = sf::Color::Transparent, sf::Color outline_hover_color = sf::Color::Transparent, sf::Color outline_active_color = sf::Color::Transparent
		);
		~Button();

		void setId(const short unsigned id);
		void setText(const std::string text);
	
		bool isPressed() const;
		short unsigned getId() const;
		const std::string getText() const;

		void update(const sf::Vector2f& mousePos);
		void render(sf::RenderTarget& target);

	};


	class DropDownList
	{
	private:
		float keyTime;
		float keyTimeMax;
		bool showList;

		sf::Font& font;
		gui::Button* activeElement;
		std::vector<gui::Button*> list;

		bool getKeyTime();
		void updateKeyTime(const float& dt);

	public:
		DropDownList(
			float x, float y, float width, float height, unsigned int char_size,
			sf::Font& font, const std::vector<std::string>& list, unsigned int index = 0
		);
		~DropDownList();

		short unsigned getActiveId();

		void update(const sf::Vector2f& mousePos, const float& dt);
		void render(sf::RenderTarget& target);

	};


	class TextureSelector 
	{
	private:
		bool active;
		float gridSize;
		sf::RectangleShape bounds;
		sf::Sprite sheet;
		sf::RectangleShape selector;
		sf::IntRect textureRect;

	public:
		TextureSelector(
			float x, float y, float width, float height,
			const sf::Texture& textureSheet, float grid_size
		);
		~TextureSelector();

		const sf::IntRect& getTextureRect() const;
		bool isActive() const;

		void selectTexture(const sf::Vector2i& mousePosWindow);

		void update(const sf::Vector2i& mousePosWindow);
		void render(sf::RenderTarget& target);
		};
}


