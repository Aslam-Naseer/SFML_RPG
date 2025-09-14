	#include "stdafx.h"
	#include "Inventory.h"

	void Inventory::nullify(unsigned from)
	{
		for (int i = from; i < items.size(); i++)
			items[i] = nullptr;
	}

	void Inventory::reserve(int capacity)
	{
		items.reserve(capacity);
	}

	Inventory::Inventory(int capacity):
		capacity(capacity)
	{
		reserve(capacity);
	}

	Inventory::~Inventory()
	{
		clear();
	}


	size_t Inventory::size() const
	{
		return items.size();
	}

	size_t Inventory::maxSize() const
	{
		return items.capacity();
	}

	void Inventory::clear()
	{
		for (Item* item : items)
			delete item;

		nullify();
	}

	bool Inventory::empty() const
	{
		return items.empty();
	}


	bool Inventory::add(Item* item)
	{
		if (items.size() == capacity)
			return false;

		items.push_back(item->clone());
		return true;
	}

	bool Inventory::remove(unsigned index)
	{
		if (items.size() == 0 || items.size() <= index)
			return false;

		delete items[index];
		items[index] = items.back();

		items.pop_back();

		return true;
	}

	bool Inventory::remove(Item* item)
	{
		for (unsigned i = 0; i < items.size(); ++i) {
			if (items[i] == item) {
				return remove(i);
			}
		}
		return false;
	}


	bool Inventory::saveToFile(const std::string fileName)
	{
		// implement when necessary
		return false;
	}

	bool Inventory::loadFromFile(const std::string fileName)
	{
		// implement when necessary
		return false;
	}