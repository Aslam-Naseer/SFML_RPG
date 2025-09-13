#pragma once

#include "State.h"
#include "PauseMenu.h"
#include "Player.h"
#include "TileMap.h"
#include "PlayerGui.h"
#include "Rat.h"

class GameState :
    public State
{
private:
	Player* player; 
	PauseMenu pmenu;
	TileMap tileMap;
	PlayerGui* playerGui;

	sf::View view;
	sf::Sprite renderSprite;
	sf::RenderTexture renderTexture;
	sf::Shader coreShader;

	std::vector<Enemy*> activeEnemies;

	void initDeferredRender();
	void initView();
    void initKeybinds();
	void initTextures();
    void initGui();
	void initShader();

public:
	GameState(StateData& state_data, sf::Font& font);
	virtual ~GameState();

	void updatePlayerInput(const float& dt);
	void updateGui(const float& dt);
	void updatePauseMenuButtons(const float& dt);
	void updateTestControls(const float& dt);
    void updateInput(const float& dt) override;

    void update(const float& dt) override;
	void render(sf::RenderTarget* target = nullptr) override;
};

