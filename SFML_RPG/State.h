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

	virtual void initKeybinds() = 0;

public:
	State(sf::RenderWindow* window, const std::map<std::string, sf::Keyboard::Scancode>& supportedKeys);
	virtual ~State();

	void checkForQuit();
	const bool& getQuit() const;

	virtual void endState() = 0;
	virtual void updateInput(const float& dt) = 0;
	virtual void update(const float &dt) = 0;
	virtual void render(sf::RenderTarget *target = nullptr) = 0;
};

