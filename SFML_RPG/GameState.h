#pragma once
#include "State.h"

class GameState :
    public State
{
private:
	Entity player; // Example entity, can be removed or modified as needed

public:
    GameState(sf::RenderWindow* window);
    virtual ~GameState();

	void endState() override;
    void update(const float& dt) override;
	void render(sf::RenderTarget* target = nullptr) override;
};

