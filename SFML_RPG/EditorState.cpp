#include "EditorState.h"

void EditorState::initKeybinds()
{
	std::ifstream ifs("Config/editorstate_keybinds.ini");

	std::string key, key_code;
	while (ifs >> key >> key_code)
		keybinds[key] = supportedKeys.at(key_code);

	ifs.close();
}

void EditorState::initFonts()
{
	if (!font.openFromFile("Fonts/Dosis-Light.ttf")) {
		throw std::runtime_error("ERROR::GAME::FONT_NOT_AVAILABLE");
	}
}

void EditorState::initButtons()
{
	// DDL test
	ddl = new gui::DropDownList(
		50.f, 50.f, 120.f, 30.f,
		font, std::vector<std::string>{ "Easy", "Medium", "Hard" }, 0
	);

}

EditorState::EditorState(sf::RenderWindow* window, const std::map<std::string, sf::Keyboard::Scancode>& supportedKeys, std::stack<State*>& states) :
	State(window, supportedKeys, states)
{
	initKeybinds();
	initFonts();
	initButtons();

}

EditorState::~EditorState()
{
	for (auto& it : buttons)
	{
		delete it.second;
	}
}

void EditorState::updateButtons()
{
	for (auto& it : buttons)
	{
		it.second->update(mousePosView);
	}

}

void EditorState::updateInput(const float& dt)
{
	if (sf::Keyboard::isKeyPressed(keybinds["CLOSE"]))
	{
		endState();
	}
}

void EditorState::update(const float& dt)
{

	updateMousePositions();
	updateButtons();
	updateInput(dt);

	ddl->update(mousePosView, dt);
}

void EditorState::render(sf::RenderTarget* target)
{
	if (!target)
		target = window;

	ddl->render(*target);
	for (auto& it : buttons)
	{
		it.second->render(*target);
	}

}
