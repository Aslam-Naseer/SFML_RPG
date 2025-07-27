#include "Game.h"

// Initialisers

void Game::initWindow()
{
	std::ifstream ifs("Config/window.ini");
	videoModes = sf::VideoMode::getFullscreenModes();

	sf::VideoMode video_mode = sf::VideoMode::getDesktopMode();
	std::string title = "None";
	bool fullscreen = false;
	unsigned int frame_rate_limit = 120;
	bool vertical_sync_enabled = false;
	int anti_aliasing_level = 0;

	if (ifs.is_open()) {
		std::getline(ifs, title);
		ifs >> video_mode.size.x >> video_mode.size.y;
		ifs >> fullscreen;
		ifs >> frame_rate_limit;
		ifs >> vertical_sync_enabled;
		ifs >> anti_aliasing_level;
	}

	ifs.close();

	sf::ContextSettings context_settings;
	context_settings.antiAliasingLevel = anti_aliasing_level;

	if (fullscreen)
	{
		window = sf::RenderWindow(video_mode, title, sf::State::Fullscreen, context_settings);
	} else 
	{
		window = sf::RenderWindow(video_mode, title, sf::Style::Titlebar | sf::Style::Close , sf::State::Windowed, context_settings);
	}

	window.setFramerateLimit(frame_rate_limit);
	window.setVerticalSyncEnabled(vertical_sync_enabled);
}

void Game::initKeys()
{
	std::ifstream ifs("Config/supported_keys.ini");

	std::string key;
	int key_code;

	while (ifs >> key >> key_code) {
		supportedKeys[key] = (sf::Keyboard::Scancode)key_code;
	}


	//DEBUG
	/*for (auto &item : supportedKeys)
		std::cout << item.first << " " << (int)item.second << std::endl;*/
}

void Game::initStates()
{
	states.push(new MainMenuState(&window, supportedKeys, states));
	//states.push(new GameState(&window, supportedKeys));
}

// Constructors and Destructors

Game::Game()
{
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
