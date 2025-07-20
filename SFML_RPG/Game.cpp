#include "Game.h"
#include "GameState.h"

// Initialisers

void Game::initWindow()
{
	std::ifstream ifs("Config/window.ini");

	sf::VideoMode video_mode = sf::VideoMode::getDesktopMode();
	std::string title = "None";
	unsigned int frame_rate_limit = 120;
	bool vertical_sync_enabled = false;

	if (ifs.is_open()) {
		std::getline(ifs, title);
		ifs >> video_mode.size.x >> video_mode.size.y;
		ifs >> frame_rate_limit;
		ifs >> vertical_sync_enabled;
	}

	ifs.close();

	window = sf::RenderWindow(video_mode, title);
	window.setFramerateLimit(frame_rate_limit);
	window.setVerticalSyncEnabled(vertical_sync_enabled);
}

void Game::initStates()
{
	states.push(new GameState(&window));
}

// Constructors and Destructors

Game::Game()
{
	initWindow();
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
