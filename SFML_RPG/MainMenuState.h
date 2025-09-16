#pragma once

#include "State.h"
#include "Gui.h"
#include "GameState.h"
#include "SettingsState.h"
#include "EditorState.h"
#include "GraphicsSettings.h"

class MainMenuState :
    public State
{
private:
    sf::RectangleShape background;
    sf::Texture bgTexture;
    std::map<std::string, sf::Font> fonts;
    std::map<std::string, gui::Button*> buttons;

    void initKeybinds();
    void initFonts();
    void initGui();
    void resetGui();

public:
	MainMenuState(StateData& state_data);
    virtual ~MainMenuState();

    void updateButtons();

    void updateInput(const float& dt) override;
    void update(const float& dt) override;

    void render(sf::RenderTarget* target = nullptr) override;

};
