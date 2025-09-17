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
	view.setSize(static_cast<sf::Vector2f>(stateData.gfxSettings->resolution.size) / 1.7f);
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
	enemySystem.loadSpawners();


	// Pause Menu
	pmenu.addButton("QUIT", utils::p2pY(70.f), "Quit");

}

void GameState::initShader()
{
	if(!coreShader.loadFromFile("Resources/Shaders/core_shader.vert", "Resources/Shaders/core_shader.frag"))
	{
		std::cout << "ERROR::GAMESTATE::COULD NOT LOAD SHADER" << "\n";
	}
}

GameState::GameState(StateData& state_data, std::map<std::string, sf::Font>& fonts):
	State(state_data), pmenu(fonts["DEFAULT"]), renderSprite(renderTexture.getTexture()),
	enemySystem(textures, tileMap), tagSystem(fonts["TEXTTAG"])
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
}

void GameState::updatePlayerInput(const float& dt)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
		player->attack();


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

void GameState::updateCombat(const float& dt)
{
	if (player->isAttacking() && player->getWeapon()->isAttackReady()) {
		auto& enemies = enemySystem.getEnemies();

		for (auto* enemy : enemies) {
			if (utils::distance(player->getCenter(), enemy->getCenter()) < player->getWeapon()->getRange()) {
				int dmg = player->getWeapon()->getDamage();

				enemy->loseHp(dmg);
				tagSystem.addTextTag(TextTagSystem::TagType::NegativeTag,
					enemy->getCenter().x, enemy->getCenter().y - 10, dmg, "-", "HP");
				
				if (enemy->isDead()) {
					player->gainExp(enemy->getExpGain());

					tagSystem.addTextTag(TextTagSystem::TagType::ExperienceTag,
						player->getCenter().x, player->getCenter().y - 10, enemy->getExpGain(), "+", "EXP");
				}
			}
		}
	}

	enemySystem.update(dt, player->getCenter());
}

void GameState::updateGui(const float& dt)
{
	playerGui->update(dt);
	tagSystem.update(dt);

	if (sf::Keyboard::isKeyPressed(keybinds["TOGGLE_TAB"]))
		playerGui->toggleTab();
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

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::E) && keyTime.consume())
		player->gainExp(20);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Q) && keyTime.consume())
		player->loseExp(20);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Up) && keyTime.consume())
		player->gainHp(1);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Down) && keyTime.consume())
		player->loseHp(1);

	// ----------------------------------------------------------------

}

void GameState::updateInput(const float& dt)
{
	if (sf::Keyboard::isKeyPressed(keybinds["CLOSE"]) && keyTime.consume())
	{
		if (!paused)
			pauseState();
		else
			unpauseState();
	}
}

void GameState::update(const float& dt)
{
	updateMousePositions(&view);
	updateInput(dt); 

	if (!paused)
	{
		updatePlayerInput(dt);
		updateCombat(dt);
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

	enemySystem.render(renderTexture, &coreShader);
	tileMap.renderSpawners(renderTexture, &coreShader);
	player->render(renderTexture, &coreShader, false);
	tileMap.renderDeferred(renderTexture, &coreShader);
	tagSystem.render(renderTexture);

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
