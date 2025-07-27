#pragma once
#include "GameState.h"
#include "Button.h"

class MainMenuState :
    public State
{
private:
    sf::RectangleShape background;
	sf::Font font;
	std::map<std::string, Button*> buttons;

    void initKeybinds();
    void initFonts();
    void initButtons();

public:
    MainMenuState(sf::RenderWindow* window, const std::map<std::string, sf::Keyboard::Scancode>& supportedKeys, std::stack<State*>& states);
    virtual ~MainMenuState();

	void updateButtons();

    void endState() override;
    void updateInput(const float& dt) override;
    void update(const float& dt) override;

    void render(sf::RenderTarget* target = nullptr) override;

};

