#pragma once

#include <iostream>
#include<vector>
#include <map>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

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

		ButtonState buttonState;

	public:

		Button(float x, float y, float width, float height,
			const std::string& text, sf::Font& font, unsigned int charSize,
			sf::Color text_idle_color, sf::Color text_hover_color, sf::Color text_active_color,
			sf::Color idle_color, sf::Color hover_color, sf::Color active_color);
		~Button();

		bool isPressed() const;

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
			float x, float y, float width, float height,
			sf::Font& font, const std::vector<std::string>& list, unsigned int index = 0
		);
		~DropDownList();

		void update(const sf::Vector2f& mousePos, const float& dt);
		void render(sf::RenderTarget& target);

	};
}


