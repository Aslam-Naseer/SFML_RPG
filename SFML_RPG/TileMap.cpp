#include "stdafx.h"
#include "TileMap.h"

TileMap::TileMap(float grid_size)
{
	gridSize = grid_size;
	mapSize = { 10, 20 };
	layers = 1;

	map = std::vector<std::vector<std::vector<Tile>>>(
		mapSize.x, std::vector<std::vector<Tile>>(
			mapSize.y, std::vector<Tile>(
				layers, Tile(0, 0, gridSize)
			)
		)
	);

	for (size_t x = 0; x < mapSize.x; x++)
	{
		for (size_t y = 0; y < mapSize.y; y++)
		{
			for (size_t z = 0; z < layers; z++)
			{
				map[x][y][z].setPosition(x * gridSize, y * gridSize);
			}
		}
	}
}

TileMap::~TileMap()
{
}

void TileMap::update()
{
}

void TileMap::render(sf::RenderTarget& target)
{
	for (size_t x = 0; x < mapSize.x; x++)
	{
		for (size_t y = 0; y < mapSize.y; y++)
		{
			for (size_t z = 0; z < layers; z++)
			{
				map[x][y][z].render(target);
			}
		}
	}
}