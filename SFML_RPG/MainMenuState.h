#pragma once
#include "GameState.h"
#include "Button.h"

class MainMenuState :
    public State
{
private:
    sf::RectangleShape background;
	sf::Font font;
    Button* button;

    void initKeybinds();
    void initFonts();

public:
    MainMenuState(sf::RenderWindow* window, const std::map<std::string, sf::Keyboard::Scancode>& supportedKeys);
    virtual ~MainMenuState();

    void endState() override;
    void updateInput(const float& dt) override;
    void update(const float& dt) override;
    void render(sf::RenderTarget* target = nullptr) override;
};

