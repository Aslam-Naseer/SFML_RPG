#pragma once
#include "State.h"

class GameState :
    public State
{
private:
	Player* player; // Example entity, can be removed or modified as needed

    void initKeybinds();
	void initTextures();
    void initPlayers();

public:
    GameState(sf::RenderWindow* window, const std::map<std::string, sf::Keyboard::Scancode>& supportedKeys, std::stack<State*>& states);
    virtual ~GameState();

    void updateInput(const float& dt) override;
    void update(const float& dt) override;
	void render(sf::RenderTarget* target = nullptr) override;
};

