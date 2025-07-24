#pragma once

#include "Entity.h"

class State
{
protected:
	sf::RenderWindow* window;
	const std::map<std::string, sf::Keyboard::Scancode>& supportedKeys;
	std::map<std::string, sf::Keyboard::Scancode> keybinds;

	std::vector<sf::Texture> textures;                         
	bool quit;

	sf::Vector2i mousePosWindow;
	sf::Vector2i mousePosScreen;
	sf::Vector2f mousePosView;

	virtual void initKeybinds() = 0;

public:
	State(sf::RenderWindow* window, const std::map<std::string, sf::Keyboard::Scancode>& supportedKeys);
	virtual ~State();

	void checkForQuit();
	const bool& getQuit() const;
	void updateMousePositions();

	virtual void endState() = 0;
	virtual void updateInput(const float& dt) = 0;
	virtual void update(const float &dt) = 0;
	virtual void render(sf::RenderTarget *target = nullptr) = 0;
};

