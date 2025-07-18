#include "Game.h"

void Game::initWindow()
{
	window = sf::RenderWindow(sf::VideoMode({ 1200, 900 }), "C++ SFML RPG");
}

Game::Game()
{
	initWindow();
}

Game::~Game()
{
}

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

	system("cls");
	std::cout << "Delta Time: " << dt << std::endl;

	updateSfmlEvents();
}

void Game::render()
{
	window.clear();

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
