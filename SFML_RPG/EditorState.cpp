#include "stdafx.h"
#include "EditorState.h"

void EditorState::initView()
{
	view.setSize(static_cast<sf::Vector2f>(stateData.gfxSettings->resolution.size));
	view.setCenter(static_cast<sf::Vector2f>(stateData.gfxSettings->resolution.size) / 2.f);
}

void EditorState::initKeybinds()
{
	std::ifstream ifs("Config/editorstate_keybinds.ini");

	std::string key, key_code;
	while (ifs >> key >> key_code)
		keybinds[key] = stateData.supportedKeys->at(key_code);

	ifs.close();
}

void EditorState::initTextures()
{
	textureRect.position.x = 0;
	textureRect.position.y = 0;
	textureRect.size.x = static_cast<int>(gridSize);
	textureRect.size.y = static_cast<int>(gridSize);
}

void EditorState::initGui()
{
	selectorRect.setSize({ gridSize, gridSize });
	selectorRect.setFillColor(sf::Color(255, 255, 255, 155));
	selectorRect.setOutlineThickness(1.f);
	selectorRect.setOutlineColor(sf::Color::White);
	
	selectorRect.setTexture(&tileMap.getTileSheet());
	selectorRect.setTextureRect(textureRect);

	textureSelector = new gui::TextureSelector(150.f, 50.f, 400.f, 900.f, tileMap.getTileSheet(), gridSize, font);

	sidebar.setSize({ gridSize * 1.5f, static_cast<float>(stateData.gfxSettings->resolution.size.x) });
	sidebar.setPosition({ 0,0 });
	sidebar.setFillColor(sf::Color(25, 25, 25, 255));
	sidebar.setOutlineColor(sf::Color(150, 150, 150, 255));
	sidebar.setOutlineThickness(1.f);
}

EditorState::EditorState(StateData& state_data, sf::Font& font) :
	State(state_data), tileMap(state_data.gridSize, 20, 20, "Resources/Images/Tilesheet.png"),
	pmenu(*window, font), gridSize(state_data.gridSize), font(font), 
	type(0), collision(false), viewSpeed(250.f)
{
	initView();
	initKeybinds();
	initTextures();
	initGui();

	pmenu.addButton("SAVE", 450.f, "Save", font);
	pmenu.addButton("LOAD", 300.f, "Load", font);

	//tileMap.loadFromFile("../tilemap.txt");
}

EditorState::~EditorState()
{
}

void EditorState::updatePauseMenuButtons(const float& dt)
{
	pmenu.update(mousePosWindow, dt);

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

		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && keyTime.isReady()) {
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
		else if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right) && keyTime.isReady()) {
			if (!textureSelector->isActive())
				tileMap.removeTile(mousePosGrid.x, mousePosGrid.y, 0);

		}
	
		selectorRect.setTextureRect(textureRect);
	}

}

void EditorState::updateInput(const float& dt)
{
	if (sf::Keyboard::isKeyPressed(keybinds["CLOSE"]) && keyTime.isReady())
	{
		if (!paused)
			pauseState();
		else
			unpauseState();
	}

	if(!paused)
	{
		
		if(sf::Keyboard::isKeyPressed(keybinds["MOVE_CAM_LEFT"]))
			view.move({ -viewSpeed * dt, 0.f });
		else if(sf::Keyboard::isKeyPressed(keybinds["MOVE_CAM_RIGHT"]))
			view.move({ viewSpeed * dt, 0.f });

		if(sf::Keyboard::isKeyPressed(keybinds["MOVE_CAM_UP"]))
			view.move({ 0.f, -viewSpeed * dt });
		else if(sf::Keyboard::isKeyPressed(keybinds["MOVE_CAM_DOWN"]))
			view.move({ 0.f, viewSpeed * dt });


		if (sf::Keyboard::isKeyPressed(keybinds["COLLISION"]) && keyTime.isReady())
			collision = !collision;
		

		if (sf::Keyboard::isKeyPressed(keybinds["TYPE_UP"]) && keyTime.isReady())
		{
			if (type < 1)
				type++;
		}
		else if (sf::Keyboard::isKeyPressed(keybinds["TYPE_DOWN"]) && keyTime.isReady())
		{
			if (type > 0)
				type--;
		}
	}
	
}

void EditorState::update(const float& dt)
{
	keyTime.update(dt);
	updateMousePositions(&view);
	updateInput(dt);

	if (!paused)
	{
		updateGui(dt);
	}

	else
	{
		updatePauseMenuButtons(dt);
	}

}

void EditorState::render(sf::RenderTarget* target)
{
	if (!target)
		target = window;

	// Render everything in view
	window->setView(view);
	tileMap.render(*target, mousePosGrid);
	tileMap.renderDeferred(*target);
	if(!textureSelector->isActive())
		target->draw(selectorRect);

	// Reset to default view for GUI
	window->setView(window->getDefaultView());

	target->draw(sidebar);
	textureSelector->render(*target);

	if (paused)
	{
		pmenu.render(*target);
	}

	//DEBUG: REMOVE LATER
	sf::Text mouseText(font,"",15);
	mouseText.setPosition({mousePosWindow.x + 20.f, mousePosWindow.y - 20.f});
	std::stringstream st;
	st << textureRect.position.x << ' ' << textureRect.position.y
		<< "\n" << "Collision: " << collision
		<< "\n" << "Type: " << type
		<< "\n" << "Layers: " << tileMap.getLayerSize(mousePosGrid.x, mousePosGrid.y, 0);
	mouseText.setString(st.str());

	target->draw(mouseText);

}
