#include "stdafx.h"
#include "EnemyEditorMode.h"

void EnemyEditorMode::initGui()
{
	float sidebarWidth = std::min(100.f, utils::p2pX(7.5f));

	// Base GUI

	selectorRect.setSize({ stateData.gridSize, stateData.gridSize });
	selectorRect.setFillColor(sf::Color(255, 255, 255, 100));
	selectorRect.setOutlineThickness(1.f);
	selectorRect.setOutlineColor(sf::Color::White);

	// Sidebar

	//sidebar.setSize({ sidebarWidth, utils::p2pY(100.f) });
	//sidebar.setPosition({ 0,0 });
	//sidebar.setFillColor(sf::Color(25, 25, 25, 200));
	//sidebar.setOutlineColor(sf::Color(150, 150, 150, 255));
	//sidebar.setOutlineThickness(1.f);
}

EnemyEditorMode::EnemyEditorMode(StateData& stateData, EditorData& editorData, TileMap& tileMap) :
	EditorMode(stateData, editorData, tileMap)
{
	initGui();
}

EnemyEditorMode::~EnemyEditorMode()
{
}

void EnemyEditorMode::updateInput(const float& dt)
{

	//if (sf::Keyboard::isKeyPressed(editorData.keybinds->at("COLLISION")) && editorData.keyTime->consume())
	//	;

	if (sf::Keyboard::isKeyPressed(editorData.keybinds->at("TYPE_UP")) && editorData.keyTime->consume())
		enemyType == 100 ? enemyType = 0 : enemyType++;

	if (sf::Keyboard::isKeyPressed(editorData.keybinds->at("TYPE_DOWN")) && editorData.keyTime->consume())
		enemyType == 0 ? enemyType = 100 : enemyType--;

	if (sf::Keyboard::isKeyPressed(editorData.keybinds->at("SPAWN_COUNT_UP")) && editorData.keyTime->consume())
	{
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::LShift))
			maxSpawns == 0 ? maxSpawns = 100 : maxSpawns--;
		else
			maxSpawns == 100 ? maxSpawns = 0 : maxSpawns++;
	}

	if (sf::Keyboard::isKeyPressed(editorData.keybinds->at("SPAWN_DELAY_UP")) && editorData.keyTime->consume())
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::LShift))
			spawnDelay == 0.f ? spawnDelay = 60.f : spawnDelay -= 0.5f;
		else
			spawnDelay == 60.f ? spawnDelay = 0.f : spawnDelay += 0.5f;
	}

	if (sf::Keyboard::isKeyPressed(editorData.keybinds->at("SPAWN_RANGE_UP")) && editorData.keyTime->consume())
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::LShift))
			spawnRange == 0.f ? spawnRange = 750.f : spawnRange -= 50.f;
		else
			spawnRange == 750.f ? spawnRange = 0.f : spawnRange += 50.f;
	}
}

void EnemyEditorMode::updateGui(const float& dt)
{

	selectorRect.setPosition({
		editorData.mousePosGrid->x * stateData.gridSize,
		editorData.mousePosGrid->y * stateData.gridSize,
		});



	if (!sidebar.getGlobalBounds().contains(static_cast<sf::Vector2f>(*editorData.mousePosWindow)))
	{

		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && editorData.keyTime->consume())
			tileMap.addSpawner(editorData.mousePosGrid->x, editorData.mousePosGrid->y, 0, 0, maxSpawns, spawnDelay, spawnRange);

		else if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right) && editorData.keyTime->consume())
			tileMap.removeSpawner(editorData.mousePosGrid->x, editorData.mousePosGrid->y, 0);
	}
}

void EnemyEditorMode::update(const float& dt)
{
	updateGui(dt);
	updateInput(dt);
}

void EnemyEditorMode::renderGui(sf::RenderTarget& target)
{
	// Render everything in view
	stateData.window->setView(*editorData.view);
	tileMap.render(target, nullptr, *editorData.mousePosGrid, true);
	tileMap.renderDeferred(target, nullptr, true);
	tileMap.renderSpawners(target, nullptr);
	target.draw(selectorRect);

	// Reset to default view for GUI
	stateData.window->setView(stateData.window->getDefaultView());

	//target.draw(sidebar);
}

void EnemyEditorMode::render(sf::RenderTarget& target)
{
	renderGui(target);

	//DEBUG: REMOVE LATER
	sf::Text mouseText(*editorData.font, "", 15);
	mouseText.setPosition({ editorData.mousePosWindow->x + 20.f, editorData.mousePosWindow->y - 20.f });
	std::stringstream st;
	st << "\n" << "Type: " << enemyType
		<< "\n" << "Count: " << maxSpawns
		<< "\n" << "Delay: " << spawnDelay
		<< "\n" << "Range: " << spawnRange;
	mouseText.setString(st.str());

	target.draw(mouseText);
}