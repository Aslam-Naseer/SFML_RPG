#include "stdafx.h"
#include "EditorMode.h"

EditorMode::EditorMode(StateData& stateData, EditorData& editorData, TileMap& tileMap):
	stateData(stateData), editorData(editorData), tileMap(tileMap)
{
}

EditorMode::~EditorMode()
{
}
