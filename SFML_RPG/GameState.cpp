#include "stdafx.h"
#include "GameState.h"

void GameState::initDeferredRender()
{
	if (!renderTexture.resize(stateData.gfxSettings->resolution.size))
	{
		std::cout << "ERROR::GAMESTATE::CANNOT_RESIZE_RENDER_TEXTURE" << "\n";
	}
	
	renderSprite.setTextureRect(sf::IntRect(
		{ 0,0 },
		static_cast<sf::Vector2i>(stateData.gfxSettings->resolution.size)
	));
}

void GameState::initView()
{
	view.setSize(static_cast<sf::Vector2f>(stateData.gfxSettings->resolution.size));
}

void GameState::initKeybinds()
{
	std::ifstream ifs("Config/gamestate_keybinds.ini");
	
	std::string key, key_code;
	while (ifs >> key >> key_code)
		keybinds[key] = stateData.supportedKeys->at(key_code);

	ifs.close();
}

void GameState::initTextures()
{
	if (!textures["PLAYER_SHEET"].loadFromFile("Resources/Sprites/Player/PLAYER_SHEET2.png"))
	{
		std::cout << "ERROR::GAMESTATE::INITTEXTURES::Could not load texture PLAYER_SHEET" << std::endl;
	}

	if (!textures["RAT_SHEET"].loadFromFile("Resources/Sprites/Enemy/RAT.png"))
	{
		std::cout << "ERROR::GAMESTATE::INITTEXTURES::Could not load texture RAT_SHEET" << std::endl;
	}
}

void GameState::initGui()
{
	// Player GUI
	player = new Player(100, 100, textures["PLAYER_SHEET"]);
	playerGui = new PlayerGui(player);


	// Tile Map
	tileMap.loadFromFile("../tilemap.txt");


	// Pause Menu
	pmenu.addButton("QUIT", utils::p2pY(70.f), "Quit");


	// Enemies
	activeEnemies.push_back(new Rat(100, 100, textures["RAT_SHEET"]));
	activeEnemies.push_back(new Rat(200, 100, textures["RAT_SHEET"]));
	activeEnemies.push_back(new Rat(200, 300, textures["RAT_SHEET"]));
	activeEnemies.push_back(new Rat(500, 500, textures["RAT_SHEET"]));
	activeEnemies.push_back(new Rat(500, 100, textures["RAT_SHEET"]));
}

void GameState::initShader()
{
	if(!coreShader.loadFromFile("Resources/Shaders/core_shader.vert", "Resources/Shaders/core_shader.frag"))
	{
		std::cout << "ERROR::GAMESTATE::COULD NOT LOAD SHADER" << "\n";
	}
}

GameState::GameState(StateData& state_data, sf::Font& font):
	State(state_data), pmenu(font), renderSprite(renderTexture.getTexture())
{
	initDeferredRender();
	initView();
	initKeybinds();
	initTextures();
	initGui();
	initShader();
}

GameState::~GameState()
{
	delete playerGui;
	delete player;

	for (auto& i : activeEnemies)
		delete i;
}

void GameState::updatePlayerInput(const float& dt)
{

	if(sf::Keyboard::isKeyPressed(keybinds["MOVE_LEFT"]))
	{
		player->move(dt, -1, 0);
	}
	if (sf::Keyboard::isKeyPressed(keybinds["MOVE_RIGHT"]))
	{
		player->move(dt, 1, 0);
	}
	if (sf::Keyboard::isKeyPressed(keybinds["MOVE_UP"]))
			{
		player->move(dt, 0, -1);
	}
	if (sf::Keyboard::isKeyPressed(keybinds["MOVE_DOWN"]))
	{
		player->move(dt, 0, 1);
	}

	player->update(dt, mousePosView);

	sf::Vector2f correctedPosition = tileMap.resolveCollision(player, dt);

	if (player->getPosition().x != correctedPosition.x)
		player->stopMovement(true, false);
	if (player->getPosition().y != correctedPosition.y)
		player->stopMovement(false, true);

	player->setPosition(correctedPosition.x, correctedPosition.y);

	sf::Vector2f mouseOffset = static_cast<sf::Vector2f>(
		mousePosWindow - static_cast<sf::Vector2i>(stateData.gfxSettings->resolution.size) / 2
		) / 15.f;

	sf::Vector2f desiredCenter = player->getPosition() + mouseOffset;
	view.setCenter(desiredCenter);
	view.setCenter(tileMap.checkViewBounds(view, { 10.f, 50.f }));
	
}

void GameState::updateGui(const float& dt)
{
	playerGui->update(dt);
}

void GameState::updatePauseMenuButtons(const float& dt)
{
	pmenu.update(mousePosWindow, dt);
	if(pmenu.isButtonPressed("QUIT"))
		endState();
}

void GameState::updateTestControls(const float& dt)
{
	// Test updates : Remove later -----------------------------------

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::E) && keyTime.isReady())
		player->gainExp(20);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Q) && keyTime.isReady())
		player->loseExp(20);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Up) && keyTime.isReady())
		player->gainHp(1);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Down) && keyTime.isReady())
		player->loseHp(1);

	// ----------------------------------------------------------------

	for (auto& enemy : activeEnemies)
	{
		//if (activeEnemies[0] == enemy || activeEnemies[3] == enemy)
		//	enemy->move(dt, 1, 0);

		enemy->update(dt);
	}
}

void GameState::updateInput(const float& dt)
{
	if (sf::Keyboard::isKeyPressed(keybinds["CLOSE"]) && keyTime.isReady())
	{
		if (!paused)
			pauseState();
		else
			unpauseState();
	}
}

void GameState::update(const float& dt)
{
	keyTime.update(dt);
	updateMousePositions(&view);
	updateInput(dt); 

	if (!paused)
	{
		updatePlayerInput(dt);
		updateGui(dt);
		updateTestControls(dt);
	}
	else
	{
		updatePauseMenuButtons(dt);
	}

}

void GameState::render(sf::RenderTarget* target)
{
	if (!target)
		target = window;

	renderTexture.clear();
	coreShader.setUniform("hasTexture", true);
	coreShader.setUniform("lightPosition", player->getCenter());

	// Currrent View 
	renderTexture.setView(view);
	tileMap.render(renderTexture, &coreShader, player->getGridPosition(static_cast<int>(stateData.gridSize)));

	for (auto& enemy : activeEnemies)
		enemy->render(renderTexture, &coreShader, true);

	player->render(renderTexture, &coreShader, false);
	tileMap.renderDeferred(renderTexture, &coreShader);

	// Window View
	renderTexture.setView(renderTexture.getDefaultView());
	playerGui->render(renderTexture);

	if (paused)
	{
		pmenu.render(renderTexture);
	}

	renderTexture.display();
	target->draw(renderSprite);

	//DEBUG: REMOVE LATER
	sf::Font font;
	if (!font.openFromFile("Fonts/Dosis-Light.ttf"))
	{
		std::cout << "ERROR::GAMESTATE::RENDER::CANNOT_RENDER_MOUSETEXT" << "\n";
	}

	sf::Text mouseText(font, "", 15);
	mouseText.setPosition({ mousePosWindow.x + 20.f, mousePosWindow.y - 20.f });
	std::stringstream st;
	st << mousePosView.x << " " << mousePosView.y <<
		"\n" << mousePosWindow.x << " " << mousePosWindow.y;
	mouseText.setString(st.str());

	target->draw(mouseText);

}
