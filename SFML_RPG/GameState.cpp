#include "stdafx.h"
#include "GameState.h"

void GameState::initDeferredRender()
{
	if (!renderTexture.resize(stateData.gfxSettings->resolution.size))
	{
		std::cout << "ERROR::GAMESTATE::CANNOT_RESIZE_RENDER_TEXTURE" << "\n";
	}
	
	renderSprite.setTextureRect(sf::IntRect(
		{ 0,0 },
		static_cast<sf::Vector2i>(stateData.gfxSettings->resolution.size)
	));
}

void GameState::initView()
{
	view.setSize(static_cast<sf::Vector2f>(stateData.gfxSettings->resolution.size));
	view.setCenter(static_cast<sf::Vector2f>(stateData.gfxSettings->resolution.size) / 2.f);
}

void GameState::initKeybinds()
{
	std::ifstream ifs("Config/gamestate_keybinds.ini");
	
	std::string key, key_code;
	while (ifs >> key >> key_code)
		keybinds[key] = stateData.supportedKeys->at(key_code);

	ifs.close();
}

void GameState::initTextures()
{
	if (!textures["PLAYER_SHEET"].loadFromFile("Resources/Sprites/Player/PLAYER_SHEET.png"))
	{
		std::cout << "ERROR::GAMESTATE::INITTEXTURES::Could not load texture PLAYER_SHEET" << std::endl;
	}
}

void GameState::initGui()
{
	// Player GUI

	sf::Vector2f spawn_point = static_cast<sf::Vector2f>(stateData.gfxSettings->resolution.size) / 2.f;
	player = new Player(spawn_point.x, spawn_point.y, textures["PLAYER_SHEET"]);

	playerGui = new PlayerGui(player);


	// Tile Map
	tileMap.loadFromFile("../tilemap.txt");


	// Pause Menu
	pmenu.addButton("QUIT", utils::p2pY(70.f), "Quit");

}

GameState::GameState(StateData& state_data, sf::Font& font):
	State(state_data), pmenu(font), renderSprite(renderTexture.getTexture())
{
	initDeferredRender();
	initView();
	initKeybinds();
	initTextures();
	initGui();
}

GameState::~GameState()
{
	delete playerGui;
	delete player;
}

void GameState::updatePlayerInput(const float& dt)
{

	if(sf::Keyboard::isKeyPressed(keybinds["MOVE_LEFT"]))
	{
		player->move(dt, -1, 0);
	}
	if (sf::Keyboard::isKeyPressed(keybinds["MOVE_RIGHT"]))
	{
		player->move(dt, 1, 0);
	}
	if (sf::Keyboard::isKeyPressed(keybinds["MOVE_UP"]))
			{
		player->move(dt, 0, -1);
	}
	if (sf::Keyboard::isKeyPressed(keybinds["MOVE_DOWN"]))
	{
		player->move(dt, 0, 1);
	}

	player->update(dt);

	sf::Vector2f correctedPosition = tileMap.resolveCollision(player, dt);

	if (player->getPosition().x != correctedPosition.x)
		player->stopMovement(true, false);
	if (player->getPosition().y != correctedPosition.y)
		player->stopMovement(false, true);

	player->setPosition(correctedPosition.x, correctedPosition.y);
	view.setCenter(player->getPosition());
	
}

void GameState::updateGui(const float& dt)
{
	playerGui->update(dt);
}

void GameState::updatePauseMenuButtons(const float& dt)
{
	pmenu.update(mousePosWindow, dt);
	if(pmenu.isButtonPressed("QUIT"))
		endState();
}

void GameState::updateTestControls(const float& dt)
{
	// Test updates : Remove later -----------------------------------

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::E) && keyTime.isReady())
		player->gainExp(20);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Q) && keyTime.isReady())
		player->loseExp(20);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Up) && keyTime.isReady())
		player->gainHp(1);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Down) && keyTime.isReady())
		player->loseHp(1);

	// ----------------------------------------------------------------
}

void GameState::updateInput(const float& dt)
{
	if (sf::Keyboard::isKeyPressed(keybinds["CLOSE"]) && keyTime.isReady())
	{
		if (!paused)
			pauseState();
		else
			unpauseState();
	}
}

void GameState::update(const float& dt)
{
	keyTime.update(dt);
	updateMousePositions();
	updateInput(dt); 

	if (!paused)
	{
		updatePlayerInput(dt);
		updateGui(dt);
		updateTestControls(dt);
	}
	else
	{
		updatePauseMenuButtons(dt);
	}

}

void GameState::render(sf::RenderTarget* target)
{
	if (!target)
		target = window;

	renderTexture.clear();

	// Currrent View 
	renderTexture.setView(view);
	tileMap.render(renderTexture, player->getGridPosition(static_cast<int>(stateData.gridSize)));
	player->render(renderTexture);
	tileMap.renderDeferred(renderTexture);

	// Window View
	renderTexture.setView(renderTexture.getDefaultView());
	playerGui->render(renderTexture);

	if (paused)
	{
		pmenu.render(renderTexture);
	}

	renderTexture.display();
	target->draw(renderSprite);

}
