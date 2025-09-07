#include "stdafx.h"
#include "GameState.h"

//void GameState::initMid()
//{
//	mid.setSize({ stateData.gridSize, stateData.gridSize });
//	mid.setFillColor(sf::Color::Cyan);
//	mid.setOrigin(mid.getSize() / 2.f);
//	mid.setPosition(static_cast<sf::Vector2f>(stateData.gfxSettings->resolution.size) / 2.f);
//}

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

void GameState::initPlayers()
{
	sf::Vector2f spawn_point = static_cast<sf::Vector2f>(stateData.gfxSettings->resolution.size) / 2.f;
	player = new Player(spawn_point.x, spawn_point.y, textures["PLAYER_SHEET"]);
}

GameState::GameState(StateData& state_data, sf::Font& font):
	State(state_data), pmenu(*window, font), renderSprite(renderTexture.getTexture())
{
	initDeferredRender();
	initView();
	initKeybinds();
	initTextures();
	initPlayers();
	//initMid();

	tileMap.loadFromFile("../tilemap.txt");
}

GameState::~GameState()
{
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

	sf::Vector2f corrected_position = tileMap.resolveCollision(player, dt);

	if (player->getPosition().x != corrected_position.x)
		player->stopMovement(true, false);
	if (player->getPosition().y != corrected_position.y)
		player->stopMovement(false, true);

	player->setPosition(corrected_position.x, corrected_position.y);
	view.setCenter(player->getPosition());
}

void GameState::updatePauseMenuButtons()
{
	if(pmenu.isButtonPressed("QUIT"))
		endState();
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
		player->update(dt);
	}
	else
	{
		pmenu.update(mousePosWindow, dt);
		updatePauseMenuButtons();
	}

}

void GameState::render(sf::RenderTarget* target)
{
	if (!target)
		target = window;

	renderTexture.clear();

	renderTexture.setView(view);
	tileMap.render(renderTexture, player->getGridPosition(stateData.gridSize));
	player->render(renderTexture);

	if (paused)
	{
		renderTexture.setView(renderTexture.getDefaultView());
		pmenu.render(renderTexture);
	}

	renderTexture.display();
	target->draw(renderSprite);

}
