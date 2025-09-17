#include "stdafx.h"
#include "DefaultEditorMode.h"

void DefaultEditorMode::initGui()
{
	float sidebarWidth = std::min(100.f, utils::p2pX(7.5f));

	// Base GUI

	selectorRect.setSize({ stateData.gridSize, stateData.gridSize });
	selectorRect.setFillColor(sf::Color(255, 255, 255, 155));
	selectorRect.setOutlineThickness(1.f);
	selectorRect.setOutlineColor(sf::Color::White);

	selectorRect.setTexture(&tileMap.getTileSheet());
	selectorRect.setTextureRect(textureRect);

	textureSelector = new gui::TextureSelector(150.f, 50.f, 900.f, 400.f, sidebarWidth, tileMap.getTileSheet(), stateData.gridSize, *editorData.font);

	// Sidebar

	sidebar.setSize({ sidebarWidth, utils::p2pY(100.f) });
	sidebar.setPosition({ 0,0 });
	sidebar.setFillColor(sf::Color(25, 25, 25, 200));
	sidebar.setOutlineColor(sf::Color(150, 150, 150, 255));
	sidebar.setOutlineThickness(1.f);
}

DefaultEditorMode::DefaultEditorMode(StateData& stateData, EditorData& editorData, TileMap& tileMap):
	EditorMode(stateData, editorData, tileMap), textureSelector(nullptr)
{
	// Texture Rect
	textureRect.position.x = 0;
	textureRect.position.y = 0;
	textureRect.size.x = static_cast<int>(stateData.gridSize);
	textureRect.size.y = static_cast<int>(stateData.gridSize);

	initGui();
}

DefaultEditorMode::~DefaultEditorMode()
{
	delete textureSelector;
}

void DefaultEditorMode::updateInput(const float& dt)
{

	if (sf::Keyboard::isKeyPressed(editorData.keybinds->at("COLLISION")) && editorData.keyTime->consume())
		collision = !collision;

	if (sf::Keyboard::isKeyPressed(editorData.keybinds->at("TYPE_UP")) && editorData.keyTime->consume())
	{
		if (type < 3)
			type++;
	}
	if (sf::Keyboard::isKeyPressed(editorData.keybinds->at("TYPE_DOWN")) && editorData.keyTime->consume())
	{
		if (type > 0)
			type--;
	}
}

void DefaultEditorMode::updateGui(const float& dt)
{
	textureSelector->update(*editorData.mousePosWindow, dt);

	if (!textureSelector->isActive())
	{
		selectorRect.setPosition({
			editorData.mousePosGrid->x * stateData.gridSize,
			editorData.mousePosGrid->y * stateData.gridSize,
			});

	}

	if (!sidebar.getGlobalBounds().contains(static_cast<sf::Vector2f>(*editorData.mousePosWindow)))
	{

		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && editorData.keyTime->consume()) {
			if (!textureSelector->isActive())
			{
				tileMap.addTile(editorData.mousePosGrid->x, editorData.mousePosGrid->y, 0, type, collision, textureRect);
			}
			else
			{
				textureRect.position.x = textureSelector->getTextureRect().position.x;
				textureRect.position.y = textureSelector->getTextureRect().position.y;
			}
		}
		else if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right) && editorData.keyTime->consume()) {
			if (!textureSelector->isActive())
				tileMap.removeTile(editorData.mousePosGrid->x, editorData.mousePosGrid->y, 0);

		}

		selectorRect.setTextureRect(textureRect);
	}
}

void DefaultEditorMode::update(const float& dt)
{
	updateGui(dt);
	updateInput(dt);
}

void DefaultEditorMode::renderGui(sf::RenderTarget& target)
{
	// Render everything in view
	stateData.window->setView(*editorData.view);
	tileMap.render(target, nullptr, *editorData.mousePosGrid, true);
	tileMap.renderDeferred(target, nullptr, true);
	if (!textureSelector->isActive())
		target.draw(selectorRect);

	// Reset to default view for GUI
	stateData.window->setView(stateData.window->getDefaultView());

	target.draw(sidebar);
	textureSelector->render(target);
}

void DefaultEditorMode::render(sf::RenderTarget& target)
{
	renderGui(target);

	//DEBUG: REMOVE LATER
	sf::Text mouseText(*editorData.font, "", 15);
	mouseText.setPosition({ editorData.mousePosWindow->x + 20.f, editorData.mousePosWindow->y - 20.f });
	std::stringstream st;
	st << textureRect.position.x << ' ' << textureRect.position.y
		<< "\n" << "Collision: " << collision
		<< "\n" << "Type: " << type
		<< "\n" << "Layers: " << tileMap.getLayerSize(editorData.mousePosGrid->x, editorData.mousePosGrid->y, 0);
	mouseText.setString(st.str());

	target.draw(mouseText);
}
