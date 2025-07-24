#include "Game.h"

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
	states.push(new MainMenuState(&window, supportedKeys));
	//states.push(new GameState(&window, supportedKeys));
}

void Game::initFonts()
{
	if (!font.openFromFile("Fonts/Dosis-Light.ttf")) {
		throw std::runtime_error("ERROR::GAME::FONT_NOT_AVAILABLE");
	}
}

// Constructors and Destructors

Game::Game()
{
	initWindow();
	initFonts();
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
