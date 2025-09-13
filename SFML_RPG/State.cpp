#include "stdafx.h"
#include "State.h"

State::State(StateData& state_data) :
	stateData(state_data), states(*state_data.states), paused(false), quit(false)
{
	window = stateData.window;
}

State::~State()
{
}

void State::endState()
{
		quit = true;
}

void State::pauseState()
{
	paused = true;
}

void State::unpauseState()
{
	paused = false;
}

const bool& State::getQuit() const
{
	return quit;
}

void State::updateMousePositions(sf::View* view)
{
	mousePosScreen = sf::Mouse::getPosition();
	mousePosWindow = sf::Mouse::getPosition(*window);
	
	if (view)
		window->setView(*view);
	
	mousePosView = window->mapPixelToCoords(mousePosWindow);
	mousePosGrid.x = static_cast<int>(mousePosView.x) / static_cast<int>(stateData.gridSize);
	mousePosGrid.y = static_cast<int>(mousePosView.y) / static_cast<int>(stateData.gridSize);

	window->setView(window->getDefaultView());
}

