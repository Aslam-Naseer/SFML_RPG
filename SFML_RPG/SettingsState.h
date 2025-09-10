#pragma once

#include "Gui.h"
#include "State.h"
#include "GraphicsSettings.h"

class SettingsState :
    public State
{
private:
    sf::RectangleShape background;
    sf::Texture bgTexture;
    sf::Font& font;
    sf::Text optionsText;

    std::map<std::string, gui::Button*> buttons;
    std::map<std::string, gui::DropDownList*> dropDownLists;
    GraphicsSettings& gfxSettings;

    void initGui();
	void initKeybinds();
    void resetGui();

public:
    SettingsState(StateData& state_data, sf::Font& font);
    virtual ~SettingsState();

    void updateGui(const float& dt);

    void updateInput(const float& dt) override;
    void update(const float& dt) override;

    void render(sf::RenderTarget* target = nullptr) override;

};