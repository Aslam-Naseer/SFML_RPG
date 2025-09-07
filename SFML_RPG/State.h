#pragma once

#include "GraphicsSettings.h"
#include "KeyTime.h"

class State;

class StateData
{
public:
	StateData();

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

	bool quit;
	bool paused;
	KeyTime keyTime;
	std::map<std::string, sf::Texture> textures;


	sf::Vector2i mousePosWindow;
	sf::Vector2i mousePosScreen;
	sf::Vector2f mousePosView;
	sf::Vector2u mousePosGrid;

	virtual void initKeybinds() = 0;

public:
	State(StateData& state_data);
	virtual ~State();

	const bool& getQuit() const;

	void endState();
	void pauseState();
	void unpauseState();

	void updateMousePositions(sf::View* view = NULL);

	virtual void updateInput(const float& dt) = 0;
	virtual void update(const float &dt) = 0;
	virtual void render(sf::RenderTarget *target = nullptr) = 0;
};

