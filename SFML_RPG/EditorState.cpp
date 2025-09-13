#include "stdafx.h"
#include "EditorState.h"

void EditorState::initView()
{
	view.setSize(static_cast<sf::Vector2f>(stateData.gfxSettings->resolution.size));
	view.setCenter(tileMap.checkViewBounds(view));
}

void EditorState::initKeybinds()
{
	std::ifstream ifs("Config/editorstate_keybinds.ini");

	std::string key, key_code;
	while (ifs >> key >> key_code)
		keybinds[key] = stateData.supportedKeys->at(key_code);

	ifs.close();
}

void EditorState::initEditorData()
{
	editorData.view = &view;
	editorData.font = &font;
	editorData.keybinds = &keybinds;
	editorData.keyTime = &keyTime;

	editorData.mousePosScreen = &mousePosScreen;
	editorData.mousePosWindow = &mousePosWindow;
	editorData.mousePosView = &mousePosView;
	editorData.mousePosGrid = &mousePosGrid;
}

void EditorState::initModes()
{
	modes.push_back(new DefaultEditorMode(stateData, editorData, tileMap));
	modes.push_back(new EnemyEditorMode(stateData, editorData, tileMap));
}

void EditorState::initGui()
{
	// Pause Menu

	pmenu.addButton("LOAD", utils::p2pY(35.f), "Load");
	pmenu.addButton("SAVE", utils::p2pY(45.f), "Save");
	pmenu.addButton("QUIT", utils::p2pY(70.f), "Quit");
}

EditorState::EditorState(StateData& state_data, sf::Font& font) :
	State(state_data), tileMap(state_data.gridSize, 30, 20, "Resources/Images/Tilesheet3.png"),
	pmenu(font), gridSize(state_data.gridSize), font(font), viewSpeed(500.f)
{
	initView();
	initKeybinds();
	initEditorData();
	initModes();
	initGui();
}

EditorState::~EditorState()
{
	for(auto& mode : modes)
	{
		delete mode;
	}
}

void EditorState::updateGui(const float& dt)
{
	if (paused)
	{
		pmenu.update(mousePosWindow, dt);

		if (pmenu.isButtonPressed("QUIT"))
			endState();

		if (pmenu.isButtonPressed("SAVE"))
			tileMap.saveToFile("../tilemap.txt");

		if (pmenu.isButtonPressed("LOAD"))
			tileMap.loadFromFile("../tilemap.txt");
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

	if (paused)
	{
		view.setCenter(tileMap.checkViewBounds(view, {100, 50}));
		return;
	}

	 //Switch Modes
	if (sf::Keyboard::isKeyPressed(keybinds["PREV_MODE"]) && keyTime.isReady())
		activeMode = activeMode == 0 ? modes.size() - 1 : activeMode - 1;

	if (sf::Keyboard::isKeyPressed(keybinds["NEXT_MODE"]) && keyTime.isReady())
		activeMode = activeMode == modes.size() - 1 ? 0 : activeMode + 1;


	// Camera movement
	sf::Vector2f movement(0.f, 0.f);
	if (sf::Keyboard::isKeyPressed(keybinds["MOVE_CAM_LEFT"]))
		movement.x -= viewSpeed * dt;
	if (sf::Keyboard::isKeyPressed(keybinds["MOVE_CAM_RIGHT"]))
		movement.x += viewSpeed * dt;
	if (sf::Keyboard::isKeyPressed(keybinds["MOVE_CAM_UP"]))
		movement.y -= viewSpeed * dt;
	if (sf::Keyboard::isKeyPressed(keybinds["MOVE_CAM_DOWN"]))
		movement.y += viewSpeed * dt;

	if (movement.x != 0.f || movement.y != 0.f)
	{
		view.move(movement);
		view.setCenter(tileMap.checkViewBounds(view, {100, 50}));
	}

}

void EditorState::update(const float& dt)
{
	keyTime.update(dt);
	updateMousePositions(&view);
	updateInput(dt);
	updateGui(dt);

	if(!paused)
		modes[activeMode]->update(dt);
}

void EditorState::render(sf::RenderTarget* target)
{
	if (!target)
		target = window;

	// render Mode
	modes[activeMode]->render(*target);

	if (paused)
	{
		pmenu.render(*target);
	}

}
