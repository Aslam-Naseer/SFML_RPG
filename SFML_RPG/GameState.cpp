#include "GameState.h"

void GameState::initKeybinds()
{
	std::ifstream ifs("Config/gamestate_keybinds.ini");
	
	std::string key, key_code;
	while (ifs >> key >> key_code)
		keybinds[key] = supportedKeys.at(key_code);

	ifs.close();

	//DEBUG
	/*for (auto& item : keybinds)
		std::cout << item.first << " " << (int)item.second << std::endl;*/
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
	player = new Player(0, 0, textures["PLAYER_SHEET"]);
}

GameState::GameState(sf::RenderWindow* window, const std::map<std::string, sf::Keyboard::Scancode>& supportedKeys, std::stack<State*>& states, sf::Font& font):
	State(window, supportedKeys, states), pmenu(*window, font)
{
	initKeybinds();
	initTextures();
	initPlayers();
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

}

void GameState::updatePauseMenuButtons()
{
	if(pmenu.isButtonPressed("QUIT"))
		endState();
}

void GameState::updateInput(const float& dt)
{
	if (sf::Keyboard::isKeyPressed(keybinds["CLOSE"]) && getKeyTime())
	{
		if (!paused)
			pauseState();
		else
			unpauseState();
	}
}

void GameState::update(const float& dt)
{
	updateMousePositions();
	updateKeyTime(dt);
	updateInput(dt); 

	if (!paused)
	{
		updatePlayerInput(dt);
		player->update(dt);
	}
	else
	{
		pmenu.update(mousePosView);
		updatePauseMenuButtons();
	}

}

void GameState::render(sf::RenderTarget* target)
{
	if (!target)
		target = window;

	player->render(*target);

	if (paused)
	{
		pmenu.render(*target);
	}
}
