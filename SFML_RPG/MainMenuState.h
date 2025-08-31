#pragma once

#include "State.h"
#include "Gui.h"
#include "GameState.h"
#include "SettingsState.h"
#include "EditorState.h"

class MainMenuState :
    public State
{
private:
    sf::RectangleShape background;
    sf::Texture bgTexture;
    sf::Font font;
    std::map<std::string, gui::Button*> buttons;

    void initBackground();
    void initKeybinds();
    void initFonts();
    void initButtons();

public:
    MainMenuState(sf::RenderWindow* window, const std::map<std::string, sf::Keyboard::Scancode>& supportedKeys, std::stack<State*>& states);
    virtual ~MainMenuState();

    void updateButtons();

    void updateInput(const float& dt) override;
    void update(const float& dt) override;

    void render(sf::RenderTarget* target = nullptr) override;

};
