#pragma once

#include "EditorMode.h"
#include "EnemySystem.h"
#include "Gui.h"

class EnemyEditorMode :
	public EditorMode
{
private:
	sf::RectangleShape selectorRect;
	sf::RectangleShape sidebar;

	int enemyType = 0;
	int spawnCount = 10;
	float spawnDelay = 60.f;
	float spawnRange = 25.f;

	void initGui();

public:
	EnemyEditorMode(StateData& stateData, EditorData& editorData, TileMap& tileMap);
	~EnemyEditorMode();


	void updateInput(const float& dt) override;
	void updateGui(const float& dt) override;
	void update(const float& dt) override;

	void renderGui(sf::RenderTarget& target) override;
	void render(sf::RenderTarget& target) override;

};

