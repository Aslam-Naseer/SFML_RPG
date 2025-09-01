#include "stdafx.h"
#include "Game.h"

// Initialisers

void Game::initGraphicsSettings()
{
	gfxSettings.loadFromFile("Config/graphics.ini");
}

void Game::initWindow()
{	
	if (gfxSettings.fullscreen)
	{
		window = sf::RenderWindow(gfxSettings.resolution, gfxSettings.title, sf::State::Fullscreen, gfxSettings.contextSettings);
	} else 
	{
		window = sf::RenderWindow(gfxSettings.resolution, gfxSettings.title, sf::Style::Titlebar | sf::Style::Close , sf::State::Windowed, gfxSettings.contextSettings);
	}

	window.setFramerateLimit(gfxSettings.frameRateLimit);
	window.setVerticalSyncEnabled(gfxSettings.verticalSync);
}

void Game::initKeys()
{
	std::ifstream ifs("Config/supported_keys.ini");

	std::string key;
	int key_code;

	while (ifs >> key >> key_code) {
		supportedKeys[key] = (sf::Keyboard::Scancode)key_code;
	}

}

void Game::initStates()
{
	states.push(new MainMenuState(&window, gfxSettings, supportedKeys, states));
}

// Constructors and Destructors

Game::Game()
{
	initGraphicsSettings();
	initWindow();
	initKeys();
	initStates();
}

Game::~Game()
{
	while (!states.empty()) {
		delete states.top();
		states.pop();
	}
}

// Functions

void Game::updateSfmlEvents()
{
	while (const std::optional event = window.pollEvent())
	{
		if (event->is<sf::Event::Closed>())
			window.close();
	}

}

void Game::update()
{
	dt = clock.restart().asSeconds();

	if (!states.empty())
	{
		states.top()->update(dt);
		if(states.top()->getQuit())
		{
			states.top()->endState();
			delete states.top();
			states.pop();
		}
	}
	else 
		window.close();

	updateSfmlEvents();
}

void Game::render()
{
	window.clear();

	if(!states.empty())
		states.top()->render();

	window.display();
}

void Game::run()
{
	while(window.isOpen())
	{
		update();
		render();
	}
}
