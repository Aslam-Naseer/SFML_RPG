#pragma once

#include "Item.h"

class Inventory
{
private:
	std::vector<Item*> items;
	int capacity = 10;

	void nullify(unsigned from = 0);
	void reserve(int capacity);

public:
	Inventory(int capacity);
	~Inventory();

	size_t size() const;
	size_t maxSize() const;

	void clear();
	bool empty() const;

	bool add(Item* item);
	bool remove(unsigned index);
	bool remove(Item* item);

	bool saveToFile(const std::string fileName);
	bool loadFromFile(const std::string fileName);
};

