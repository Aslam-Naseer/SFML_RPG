#pragma once
#include "GameState.h"

class MainMenuState :
    public State
{
private:
    sf::RectangleShape background;

    void initKeybinds();

public:
    MainMenuState(sf::RenderWindow* window, const std::map<std::string, sf::Keyboard::Scancode>& supportedKeys);
    virtual ~MainMenuState();

    void endState() override;
    void updateInput(const float& dt) override;
    void update(const float& dt) override;
    void render(sf::RenderTarget* target = nullptr) override;
};

