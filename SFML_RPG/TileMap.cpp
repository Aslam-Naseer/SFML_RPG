#include "stdafx.h"
#include "TileMap.h"

void TileMap::initMap(float grid_size, unsigned width, unsigned height, unsigned layers, std::string& texture_file)
{
	gridSize = grid_size;
	mapSize = { width, height };
	this->layers = layers;

	map = std::vector<std::vector<std::vector<Tile*>>>(
		mapSize.x, std::vector<std::vector<Tile*>>(
			mapSize.y, std::vector<Tile*>(
				layers, NULL
			)
		)
	);

	textureFile = texture_file;
	if (!tileSheet.loadFromFile(textureFile))
	{
		std::cout << "ERROR::TILEMAP::Could not load tilesheet." << std::endl;
	}
}

void TileMap::clearMap()
{
	for (size_t x = 0; x < mapSize.x; x++)
	{
		for (size_t y = 0; y < mapSize.y; y++)
		{
			for (size_t z = 0; z < layers; z++)
			{
					delete map[x][y][z];
			}
			map[x][y].clear();
		}
		map[x].clear();
	}
	map.clear();

	mapSize = { 0, 0 };
	layers = 0;
}

TileMap::TileMap()
{
	gridSize = 0;
	mapSize = { 0, 0 };
	layers = 0;
}

TileMap::TileMap(float grid_size, unsigned width, unsigned height, std::string texture_file)
{
	initMap(grid_size, width, height, 1, texture_file);
}

TileMap::~TileMap()
{
	clearMap();
}

const sf::Texture& TileMap::getTileSheet() const
{
	return tileSheet;
}

void TileMap::addTile(unsigned x, unsigned y, unsigned layer, short type, bool collision ,const sf::IntRect& textureRect)
{
	if(x < mapSize.x && y < mapSize.y && layer < layers)
	{
		if (map[x][y][layer] == NULL)
		{
			map[x][y][layer] = new Tile(x * gridSize, y * gridSize, gridSize, tileSheet, textureRect, type, collision);
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

void TileMap::saveToFile(const std::string file_name)
{
	std::ofstream ofs;
	
	ofs.open(file_name);
	if (!ofs.is_open())
	{
		std::cout << "ERROR::TILEMAP::CANNOT_SAVE_TO_FILE" << file_name << "\n";
		ofs.close();
		return;
	}

	ofs << mapSize.x << " " << mapSize.y << "\n"
		<< gridSize << "\n"
		<< layers << "\n"
		<< textureFile << "\n";

	for (size_t x = 0; x < mapSize.x; x++)
	{
		for (size_t y = 0; y < mapSize.y; y++)
		{
			for (size_t z = 0; z < layers; z++)
			{
				if (map[x][y][z] != NULL)
					ofs << x << " " << y << " " << z << " " << map[x][y][z]->toString();
			}
		}
	}

	ofs.close();
}

void TileMap::loadFromFile(const std::string file_name)
{
	std::ifstream ifs;

	ifs.open(file_name);
	if (!ifs.is_open())
	{
		std::cout << "ERROR::TILEMAP::CANNOT_LOAD_FROM_FILE" << file_name << "\n";
		ifs.close();
		return;
	}

	clearMap();

	float grid_size;
	unsigned map_size_x, map_size_y, layers;
	std::string texture_file;

	ifs >> map_size_x >> map_size_y >> grid_size >> layers >> texture_file;
	initMap(grid_size, map_size_x, map_size_y, layers, texture_file);

	unsigned x, y, z;
	short type;
	bool collisoin;
	sf::IntRect temp_rect({ 0,0 }, { static_cast<int>(grid_size), static_cast<int>(grid_size) });
	
	while (ifs >> x >> y >> z >> temp_rect.position.x >> temp_rect.position.y >> type >> collisoin)
		addTile(x, y, z, type, collisoin, temp_rect);

	ifs.close();
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