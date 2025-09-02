#pragma once

#include "GraphicsSettings.h"

class State;

class StateData
{
public:
	StateData() {};

	float gridSize;
	sf::RenderWindow* window;
	std::map<std::string, sf::Keyboard::Scancode>* supportedKeys;
	std::stack<State*>* states;
	GraphicsSettings* gfxSettings;
};

class State
{
protected:
	StateData& stateData;
	sf::RenderWindow* window;
	std::map<std::string, sf::Keyboard::Scancode> keybinds;
	std::stack<State*>& states;

	std::map<std::string, sf::Texture> textures;
	bool quit;
	bool paused;
	float keyTime;
	float maxKeyTime;

	sf::Vector2i mousePosWindow;
	sf::Vector2i mousePosScreen;
	sf::Vector2f mousePosView;

	virtual void initKeybinds() = 0;

public:
	State(StateData& state_data);
	virtual ~State();

	const bool& getQuit() const;
	const bool getKeyTime();

	void endState();
	void pauseState();
	void unpauseState();

	void updateMousePositions();
	void updateKeyTime(const float& dt);

	virtual void updateInput(const float& dt) = 0;
	virtual void update(const float &dt) = 0;
	virtual void render(sf::RenderTarget *target = nullptr) = 0;
};

