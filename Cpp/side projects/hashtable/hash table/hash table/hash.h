#pragma once

#include <cstdlib>
#include <iostream>
#include <string>

#define HASH_H

class hashtable
{
public:
	hashtable();
	int Hash(std::string);
	int IndexCount(int);
	void AddItem(std::string, std::string);
	void RemoveItem(std::string);
	void PrintTable();
	void PrintIndexItems(int index);
	void FindGoal(std::string);

private:
	static const int tableSize = 4;
	struct item
	{
		std::string name;
		std::string goal;
		item* next;
	};

	item* HashTable[tableSize];
};