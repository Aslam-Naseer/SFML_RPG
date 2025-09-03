#include "stdafx.h"
#include "TileMap.h"

TileMap::TileMap(float grid_size)
{
	gridSize = grid_size;
	mapSize = { 100, 100 };
	layers = 1;

	map = std::vector<std::vector<std::vector<Tile*>>>(
		mapSize.x, std::vector<std::vector<Tile*>>(
			mapSize.y, std::vector<Tile*>(
				layers, NULL
			)
		)
	);

}

TileMap::~TileMap()
{
	for (size_t x = 0; x < mapSize.x; x++)
	{
		for (size_t y = 0; y < mapSize.y; y++)
		{
			for (size_t z = 0; z < layers; z++)
			{
				if (map[x][y][z] != NULL)
					delete map[x][y][z];
			}
		}
	}
}

void TileMap::addTile(unsigned x, unsigned y, unsigned layer)
{
	if(x < mapSize.x && y < mapSize.y && layer < layers)
	{
		if (map[x][y][layer] == NULL)
		{
			map[x][y][layer] = new Tile(x * gridSize, y * gridSize, gridSize);
		}
	}
}

void TileMap::removeTile(unsigned x, unsigned y, unsigned layer)
{
	if (x < mapSize.x && y < mapSize.y && layer < layers)
	{
		if (map[x][y][layer] != NULL)
		{
			delete map[x][y][layer];
			map[x][y][layer] = NULL;
		}
	}
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
				if (map[x][y][z] != NULL)
					map[x][y][z]->render(target);
			}
		}
	}
}