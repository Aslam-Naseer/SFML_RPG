#include "stdafx.h"
#include "EditorState.h"

void EditorState::initKeybinds()
{
	std::ifstream ifs("Config/editorstate_keybinds.ini");

	std::string key, key_code;
	while (ifs >> key >> key_code)
		keybinds[key] = stateData.supportedKeys->at(key_code);

	for(auto& i : keybinds)
		std::cout << i.first << " ";

	ifs.close();
}

void EditorState::initTextures()
{
	textureRect.position.x = 0;
	textureRect.position.y = 0;
	textureRect.size.x = 100;
	textureRect.size.y = 100;
}

void EditorState::initGui()
{
	selectorRect.setSize({ gridSize, gridSize });
	selectorRect.setFillColor(sf::Color(255, 255, 255, 155));
	selectorRect.setOutlineThickness(1.f);
	selectorRect.setOutlineColor(sf::Color::White);
	
	selectorRect.setTexture(&tileMap.getTileSheet());
	selectorRect.setTextureRect(textureRect);

	textureSelector = new gui::TextureSelector(150.f, 50.f, 400.f, 500.f, tileMap.getTileSheet(), gridSize, font);

	sidebar.setSize({ gridSize, static_cast<float>(stateData.gfxSettings->resolution.size.x) });
	sidebar.setPosition({ 0,0 });
	sidebar.setFillColor(sf::Color(25, 25, 25, 255));
	sidebar.setOutlineColor(sf::Color(150, 150, 150, 255));
	sidebar.setOutlineThickness(1.f);
}

EditorState::EditorState(StateData& state_data, sf::Font& font) :
	State(state_data), tileMap(state_data.gridSize, 50, 50, "Resources/Images/Tilesheet.png"),
	pmenu(*window, font), gridSize(state_data.gridSize), font(font), type(0), collision(false)
{
	initKeybinds();
	initTextures();
	initGui();

	pmenu.addButton("SAVE", 550.f, "Save", font);
	pmenu.addButton("LOAD", 300.f, "Load", font);
}

EditorState::~EditorState()
{
}

void EditorState::updatePauseMenuButtons()
{
	if (pmenu.isButtonPressed("QUIT"))
		endState();

	if (pmenu.isButtonPressed("SAVE"))
		tileMap.saveToFile("../tilemap.txt");

	if (pmenu.isButtonPressed("LOAD"))
		tileMap.loadFromFile("../tilemap.txt");
}

void EditorState::updateGui(const float& dt)
{
	textureSelector->update(mousePosWindow, dt);

	if (!textureSelector->isActive())
	{
		selectorRect.setPosition({
			mousePosGrid.x * gridSize,
			mousePosGrid.y * gridSize,
			});

	}

	if (!sidebar.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosWindow)))
	{

		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && getKeyTime()) {
			if (!textureSelector->isActive())
			{
				tileMap.addTile(mousePosGrid.x, mousePosGrid.y, 0, type, collision, textureRect);
			}
			else
			{
				textureRect.position.x = textureSelector->getTextureRect().position.x;
				textureRect.position.y = textureSelector->getTextureRect().position.y;
			}
		}
		else if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right) && getKeyTime()) {
			if (!textureSelector->isActive())
				tileMap.removeTile(mousePosGrid.x, mousePosGrid.y, 0);

		}
	
		selectorRect.setTextureRect(textureRect);
	}

}

void EditorState::updateInput(const float& dt)
{
	if (sf::Keyboard::isKeyPressed(keybinds["CLOSE"]) && getKeyTime())
	{
		if (!paused)
			pauseState();
		else
			unpauseState();
	}

	if(!paused)
	{

		if (sf::Keyboard::isKeyPressed(keybinds["COLLISION"]) && getKeyTime())
		{
			std::cout << "Collision\n";
			collision = !collision;
		}

		if (sf::Keyboard::isKeyPressed(keybinds["TYPE_UP"]) && getKeyTime())
		{
			std::cout << "Type up\n";
			type++;
		}
		else if (sf::Keyboard::isKeyPressed(keybinds["TYPE_DOWN"]) && getKeyTime())
		{
			std::cout << "Type down\n";

			if (type > 0)
				type--;
		}
	}
	
}

void EditorState::update(const float& dt)
{
	updateMousePositions();
	updateKeyTime(dt);
	updateInput(dt);

	if (!paused)
	{
		updateGui(dt);
	}

	else
	{
		pmenu.update(mousePosView, dt);
		updatePauseMenuButtons();
	}

}

void EditorState::render(sf::RenderTarget* target)
{
	if (!target)
		target = window;

	tileMap.render(*target);

	if(!textureSelector->isActive())
		target->draw(selectorRect);

	target->draw(sidebar);
	textureSelector->render(*target);

	if (paused)
	{
		pmenu.render(*target);
	}

	//DEBUG: REMOVE LATER
	sf::Text mouseText(font,"",15);
	mouseText.setPosition({mousePosView.x + 20, mousePosView.y - 20});
	std::stringstream st;
	st << textureRect.position.x << ' ' << textureRect.position.y
		<< "\n" << "Collision: " << collision
		<< "\n" << "Type: " << type;
	mouseText.setString(st.str());

	target->draw(mouseText);

}
