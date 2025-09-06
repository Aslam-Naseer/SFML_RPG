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

	sf::View view;
	sf::Sprite renderSprite;
	sf::RenderTexture renderTexture;


	//sf::RectangleShape mid;
	//void initMid();

	void initDeferredRender();
	void initView();
    void initKeybinds();
	void initTextures();
    void initPlayers();

public:
	GameState(StateData& state_data, sf::Font& font);
	virtual ~GameState();

	void updatePlayerInput(const float& dt);
	void updatePauseMenuButtons();
    void updateInput(const float& dt) override;

    void update(const float& dt) override;
	void render(sf::RenderTarget* target = nullptr) override;
};

