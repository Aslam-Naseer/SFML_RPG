#pragma once

#include "Player.h"

class State
{
protected:
	sf::RenderWindow* window;
	const std::map<std::string, sf::Keyboard::Scancode>& supportedKeys;
	std::map<std::string, sf::Keyboard::Scancode> keybinds;
	std::stack<State*>& states;

	std::map<std::string, sf::Texture> textures;
	bool quit;

	sf::Vector2i mousePosWindow;
	sf::Vector2i mousePosScreen;
	sf::Vector2f mousePosView;

	virtual void initKeybinds() = 0;

public:
	State(sf::RenderWindow* window, const std::map<std::string, sf::Keyboard::Scancode>& supportedKeys, std::stack<State*>& states);
	virtual ~State();

	void endState();
	const bool& getQuit() const;
	void updateMousePositions();

	virtual void updateInput(const float& dt) = 0;
	virtual void update(const float &dt) = 0;
	virtual void render(sf::RenderTarget *target = nullptr) = 0;
};

