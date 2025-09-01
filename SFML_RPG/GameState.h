#pragma once

#include "State.h"
#include "PauseMenu.h"
#include "Player.h"
#include "TileMap.h"

class GameState :
    public State
{
private:
	Player* player; 
	PauseMenu pmenu;
	TileMap tileMap;

    void initKeybinds();
	void initTextures();
    void initPlayers();

public:
    GameState(sf::RenderWindow* window, const std::map<std::string, sf::Keyboard::Scancode>& supportedKeys, std::stack<State*>& states, sf::Font& font);
    virtual ~GameState();

	void updatePlayerInput(const float& dt);
	void updatePauseMenuButtons();
    void updateInput(const float& dt) override;

    void update(const float& dt) override;
	void render(sf::RenderTarget* target = nullptr) override;
};

