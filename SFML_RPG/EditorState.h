#pragma once

#include "State.h"
#include "Gui.h"

class EditorState :
    public State
{
private:

    sf::Font font;
    std::map<std::string, gui::Button*> buttons;
	gui::DropDownList* ddl;

    void initKeybinds();
    void initFonts();
    void initButtons();

public:
    EditorState(StateData& state_data);
    virtual ~EditorState();

    void updateButtons();

    void updateInput(const float& dt) override;
    void update(const float& dt) override;

    void render(sf::RenderTarget* target = nullptr) override;
};

