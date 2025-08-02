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
	if (!textures["IDLE_PLAYER"].loadFromFile("Resources/Sprites/Player/test.png"))
	{
		std::cout << "ERROR::GAMESTATE::INITTEXTURES::Could not load texture IDLE_PLAYER" << std::endl;
	}
}

void GameState::initPlayers()
{
	player = new Player(0, 0, textures["IDLE_PLAYER"]);
}

GameState::GameState(sf::RenderWindow* window, const std::map<std::string, sf::Keyboard::Scancode>& supportedKeys, std::stack<State*>& states):
	State(window, supportedKeys, states)
{
	initKeybinds();
	initTextures();
	initPlayers();
}

GameState::~GameState()
{
	delete player;
}

void GameState::updateInput(const float& dt)
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

	if (sf::Keyboard::isKeyPressed(keybinds["CLOSE"]))
	{
		endState();
	}
}

void GameState::update(const float& dt)
{

	updateMousePositions();
	updateInput(dt);
}

void GameState::render(sf::RenderTarget* target)
{
	if (!target)
		target = window;

	player->render(target);
}
