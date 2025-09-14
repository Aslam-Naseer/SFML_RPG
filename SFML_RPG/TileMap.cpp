#include "stdafx.h"
#include "TileMap.h"

void TileMap::initMap(float grid_size, int width, int height, int layers, std::string& texture_file)
{
	gridSize = grid_size;
	mapSize = { width, height };
	this->layers = layers;

	map = std::vector<std::vector<std::vector<std::vector<Tile*>>>>(
		mapSize.x, std::vector<std::vector<std::vector<Tile*>>>(
			mapSize.y, std::vector<std::vector<Tile*>>(
				layers, std::vector<Tile*>()
			)
		)
	);

	textureFile = texture_file;
	if (!tileSheet.loadFromFile(textureFile))
	{
		std::cout << "ERROR::TILEMAP::Could not load tilesheet." << std::endl;
	}

	collisionBox.setSize({ gridSize, gridSize });
	collisionBox.setFillColor(sf::Color(255, 0, 0, 100));
	collisionBox.setOutlineColor(sf::Color::Red);
	collisionBox.setOutlineThickness(1.f);

	mapBorder.setSize({ width * grid_size, height * grid_size });
	mapBorder.setPosition({ 0.f, 0.f });
	mapBorder.setFillColor(sf::Color::Transparent);
	mapBorder.setOutlineColor(sf::Color::White);
	mapBorder.setOutlineThickness(-2.f);
}

void TileMap::clearMap()
{
	for (size_t x = 0; x < mapSize.x; x++)
	{
		for (size_t y = 0; y < mapSize.y; y++)
		{
			for (size_t z = 0; z < layers; z++)
			{
				for (auto& tile : map[x][y][z])
				{
					delete tile;
				}
				map[x][y][z].clear();
			}
			map[x][y].clear();
		}
		map[x].clear();
	}
	map.clear();


	for(auto& [pos, layerMap] : spawners)
	{
		for(auto& [layer, spawner] : layerMap)
		{
			delete spawner;
		}
		layerMap.clear();
	}


	mapSize = { 0, 0 };
	layers = 0;
}

bool TileMap::isValidCoordinate(int x, int y, int layer) const 
{
	return x >= 0 && y >= 0 && layer >= 0 &&
		x < mapSize.x && y < mapSize.y && layer < layers;
}


TileMap::TileMap()
{
	gridSize = 0;
	mapSize = { 0, 0 };
	layers = 0;
}

TileMap::TileMap(float grid_size, int width, int height, std::string texture_file)
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

const sf::Vector2f TileMap::getMapSize() const
{
	return mapBorder.getSize();
}

const int TileMap::getLayerSize(const int x, const int y, const int layer) const
{
	if (!isValidCoordinate(x, y, layer))
		return -1;

	return static_cast<int>(map[x][y][layer].size());
}

sf::Vector2f TileMap::checkViewBounds(const sf::View& view, sf::Vector2f padding) const
{
	sf::Vector2f viewSize = view.getSize();
	sf::Vector2f viewCenter = view.getCenter();
	sf::Vector2f mapSizeF = mapBorder.getSize();
	sf::Vector2f mapPos = mapBorder.getPosition();

	if(mapSizeF.x < viewSize.x)
		viewCenter.x = mapPos.x + mapSizeF.x / 2.f;
	else
		viewCenter.x = std::clamp(viewCenter.x, viewSize.x / 2.f - padding.x , mapSizeF.x - viewSize.x / 2.f + padding.x);

	if (mapSizeF.y < viewSize.y)
		viewCenter.y = mapPos.y + mapSizeF.y / 2.f;
	else
		viewCenter.y = std::clamp(viewCenter.y, viewSize.y / 2.f - padding.y, mapSizeF.y - viewSize.y / 2.f + padding.y); 

	return viewCenter;
}

sf::Vector2f TileMap::resolveCollision(const Entity* entity, const float& dt) const
{
	// World Border

	sf::Vector2f resolvedPos = entity->getPosition();

	float mapWidth = getMapSize().x, mapHeight = getMapSize().y;
	float entityWidth = entity->getGlobalBounds().size.x, entityHeight = entity->getGlobalBounds().size.y;

	resolvedPos.x = std::clamp(resolvedPos.x, 0.f, mapWidth - entityWidth);
	resolvedPos.y = std::clamp(resolvedPos.y, 0.f, mapHeight - entityHeight);


	// Tile Collision

	sf::Vector2i gridPos = entity->getGridPosition(static_cast<int>(gridSize));
	sf::Vector2i cullSize = { 7, 7 };

	int startX = std::clamp(gridPos.x - cullSize.x / 2, 0, static_cast<int>(mapSize.x));
	int startY = std::clamp(gridPos.y - cullSize.y / 2, 0, static_cast<int>(mapSize.y));
	int endX = std::clamp(gridPos.x + cullSize.x / 2 + 1, 0, static_cast<int>(mapSize.x));
	int endY = std::clamp(gridPos.y + cullSize.y / 2 + 1, 0, static_cast<int>(mapSize.y));

	int layer = 0;
	sf::FloatRect entityBounds = entity->getGlobalBounds();
	sf::FloatRect nextBounds = entity->getNextPosBounds(dt);

	bool resolveX = false, resolveY = false;
	float correctedX = resolvedPos.x, correctedY = resolvedPos.y;

	for (int x = startX; x < endX; x++) {
		for (int y = startY; y < endY; y++) {
			for (int k = 0; k < map[x][y][layer].size(); k++)
			{
				if (!map[x][y][layer][k] || !map[x][y][layer][k]->collision)
					continue;

				if (!map[x][y][layer][k]->intersects(nextBounds))
					continue;

				sf::FloatRect tileBounds = map[x][y][layer][k]->shape.getGlobalBounds();

				float nextLeft = nextBounds.position.x;
				float nextRight = nextBounds.position.x + nextBounds.size.x;
				float nextTop = nextBounds.position.y;
				float nextBot = nextBounds.position.y + nextBounds.size.y;

				float tileLeft = tileBounds.position.x;
				float tileRight = tileBounds.position.x + tileBounds.size.x;
				float tileTop = tileBounds.position.y;
				float tileBot = tileBounds.position.y + tileBounds.size.y;

				float overlapLeft = nextRight - tileLeft;
				float overlapRight = tileRight - nextLeft;
				float overlapTop = nextBot - tileTop;
				float overlapBottom = tileBot - nextTop;

				float minOverlapX = std::min(overlapLeft, overlapRight);
				float minOverlapY = std::min(overlapTop, overlapBottom);

				if (minOverlapX < minOverlapY)
				{
					if (overlapLeft < overlapRight)
						correctedX = tileLeft - entityWidth;
					else
						correctedX = tileRight;

					resolveX = true;
				}
				else
				{
					if (overlapTop < overlapBottom)
						correctedY = tileTop - entityHeight;
					else
						correctedY = tileBot;

					resolveY = true;
				}
			}
			
		}
	}

	if (resolveX)
		resolvedPos.x = correctedX;
	if (resolveY)
		resolvedPos.y = correctedY;

	return resolvedPos;
}

void TileMap::addTile(int x, int y, int layer, short type, bool collision, const sf::IntRect& textureRect)
{
	if (!isValidCoordinate(x, y, layer))
		return;

	Tile::Type tileType = static_cast<Tile::Type>(type);

	auto& tileLayer = map[x][y][layer];
	if (!tileLayer.empty() && tileLayer.back()->shape.getTextureRect() == textureRect)
		return;

	tileLayer.push_back(
		new Tile(x * gridSize, y * gridSize, tileSheet, textureRect, tileType, collision)
	);
}

void TileMap::addSpawner(int x, int y, int layer, int enemyType, int spawnCount, float spawnDelay, float spawnRange)
{
	if (!isValidCoordinate(x, y, layer))
		return;

	sf::Vector2i pos = { x, y };
	if (spawners.find(pos) != spawners.end())
	{
		if (spawners[pos].count(layer) > 0)
			return;
	}

	spawners[pos][layer] = new EnemySpawner(
		x * gridSize, y * gridSize, gridSize,
		enemyType, spawnCount, spawnDelay, spawnRange
	);
}

void TileMap::removeTile(int x, int y, int layer)
{
	if (!isValidCoordinate(x, y, layer))
		return;

	if (!map[x][y][layer].empty())
	{
		delete map[x][y][layer][map[x][y][layer].size() - 1];
		map[x][y][layer].pop_back();
	}
}

void TileMap::removeSpawner(int x, int y, int layer)
{
	if(!isValidCoordinate(x, y, layer))
		return;

	sf::Vector2i pos = { x, y };
	if (spawners.count(pos) == 0 || spawners[pos].count(layer) == 0)
			return;

	delete spawners[pos][layer];
	spawners[pos].erase(layer);

	if(spawners[pos].empty())
		spawners.erase(pos);
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

	// Tile saving

	for (size_t x = 0; x < mapSize.x; x++)
	{
		for (size_t y = 0; y < mapSize.y; y++)
		{
			for (size_t z = 0; z < layers; z++)
			{
				if (!map[x][y][z].empty())
				{
					for (auto& tile : map[x][y][z])
					{
						ofs << x << " " << y << " " << z << " " << tile->toString() << "\t";
					}
				}
			}
		}
	}

	// Spawner saving

	ofs << "\n" << "SPAWNERS" << "\n";

	for (auto& [pos, layerMap] : spawners)
	{
		for (auto& [layer, spawner] : layerMap)
		{
			ofs << pos.x << " " << pos.y << " " << layer << " " << spawner->toString() << "\t";
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

	// Tile loading

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


	// Spawner loading

	ifs.clear();
	std::string marker;
	ifs >> marker;

	if (marker != "SPAWNERS")
	{
		ifs.close();
		return;
	}

	int enemyType, spawnCount;
	float spawnDelay, spawnRange;

	while (ifs >> x >> y >> z >> enemyType >> spawnCount >> spawnDelay >> spawnRange)
		addSpawner(x, y, z, enemyType, spawnCount, spawnDelay, spawnRange);


	ifs.close();
}

void TileMap::update()
{
}

void TileMap::renderSpawners(sf::RenderTarget& target, sf::Shader* shader)
{
	for (auto& [pos, layerMap] : spawners)
	{
		//if (pos.x < start_x || pos.x >= end_x || pos.y < start_y || pos.y >= end_y)
		//	continue;

		for (auto& [layer, spawner] : layerMap)
			spawner->render(target);
	}
}

void TileMap::renderDeferred(sf::RenderTarget& target, sf::Shader* shader, bool showCollision)
{
	while (!deferredRenderStack.empty())
	{
		auto& tile = deferredRenderStack.top();

		tile->render(target, shader);
		if (showCollision && tile->collision)
		{
			collisionBox.setPosition(tile->shape.getPosition());
			target.draw(collisionBox);
		}

		deferredRenderStack.pop();
	}

	target.draw(mapBorder);

}

void TileMap::render(sf::RenderTarget& target, sf::Shader* shader, const sf::Vector2i& gridPosition, bool showCollision)
{

	sf::View currentView = target.getView();
	sf::Vector2f viewSize = currentView.getSize();

	sf::Vector2i cull_size = {
		static_cast<int>(viewSize.x / gridSize) * 2 ,
		static_cast<int>(viewSize.y / gridSize) * 2 
	};

	int start_x = std::clamp(gridPosition.x - cull_size.x / 2, 0, static_cast<int>(mapSize.x));
	int start_y = std::clamp(gridPosition.y - cull_size.y / 2, 0, static_cast<int>(mapSize.y));
	int end_x = std::clamp(gridPosition.x + cull_size.x / 2 + 1, 0, static_cast<int>(mapSize.x));
	int end_y = std::clamp(gridPosition.y + cull_size.y / 2 + 1, 0, static_cast<int>(mapSize.y));

	int layer = 0;
	for (int x = start_x; x < end_x; x++) {
		for (int y = start_y; y < end_y; y++) {
			for (auto& tile : map[x][y][layer])
			{
				if(tile->type == Tile::Type::Floating)
				{
					deferredRenderStack.push(tile);
				}
				else
				{
					tile->render(target, shader);
					if (showCollision && tile->collision) 
					{
						collisionBox.setPosition(tile->shape.getPosition());
						target.draw(collisionBox);
					}
				}
			}

		}
	}
}

