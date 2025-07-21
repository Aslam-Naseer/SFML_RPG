#pragma once
#include "State.h"

class GameState :
    public State
{
private:
	Entity player; // Example entity, can be removed or modified as needed

    void initKeybinds();

public:
    GameState(sf::RenderWindow* window, const std::map<std::string, sf::Keyboard::Scancode>& supportedKeys);
    virtual ~GameState();

	void endState() override;
    void updateInput(const float& dt) override;
    void update(const float& dt) override;
	void render(sf::RenderTarget* target = nullptr) override;
};

