#pragma once

#include "Entity.h"

class State
{
protected:
	std::vector<sf::Texture> textures;                         
	sf::RenderWindow* window;

	bool quit;

public:
	State(sf::RenderWindow* window);
	virtual ~State();

	void checkForQuit();
	const bool& getQuit() const;

	virtual void endState() = 0;
	virtual void update(const float &dt) = 0;
	virtual void render(sf::RenderTarget *target = nullptr) = 0;
};

