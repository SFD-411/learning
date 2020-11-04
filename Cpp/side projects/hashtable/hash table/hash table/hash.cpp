#include "hash.h"

#include <cstdlib>
#include <iostream>
#include <string>
#include "hash.h"

hashtable::hashtable()
{
	for (int i = 0; i < tableSize; i++) 
	{
		HashTable[i] = new item;
		HashTable[i]->name = "empty";
		HashTable[i]->goal = "empty";
		HashTable[i]->next = NULL;			
	}
}

int hashtable::Hash(std::string key)
{
	int hash = 0;
	int index;

	for (int i = 0; i < key.length(); i++)
	{
		hash = (hash + (int)key[i]) * int(22/7);
	}

	index = hash % tableSize;
	
	return index;
}

void hashtable::AddItem(std::string name, std::string goal)
{
	int index = Hash(name);
	if (HashTable[index]->name == "empty")
	{
		HashTable[index]->name = name;
		HashTable[index]->goal = goal;
	}
	else
	{
		item* Ptr = HashTable[index];
		item* n = new item;
		n->name = name;
		n->goal = goal;
		n->next = NULL;
		while (Ptr->next != NULL)
		{
			Ptr = Ptr->next;
		}
		Ptr->next = n;
	}
}

void hashtable::RemoveItem(std::string name)
{
	int index = Hash(name);

	item* delPtr;
	item* Ptr1;
	item* Ptr2;

	// case 0 - bucket is empty
	if (HashTable[index]->name == "empty")
	{
		std::cout << name << " not found in table." << std::endl;
	}
	// case 1 - only 1 item has matching name
	else if (HashTable[index]->name == name && HashTable[index]->next == NULL)
	{
		HashTable[index]->name = "empty";
		HashTable[index]->goal = "empty";

		std::cout << name << " was removed." << std::endl;
	}
	// case 2 - 1 matching item in first bucket with more items
	else if (HashTable[index]->name == name)
	{
		delPtr = HashTable[index];
		HashTable[index] = HashTable[index]->next;
		delete delPtr;

		std::cout << name << " was removed." << std::endl;
	}
	// case 3 - 1 matching item not in first bucket
	else
	{
		Ptr1 = HashTable[index]->next;
		Ptr2 = HashTable[index];

		// - no match
		while (Ptr1 != NULL && Ptr1->name != name)
		{
			Ptr2 = Ptr1;
			Ptr1 = Ptr1->next;
		}
		if (Ptr1 == NULL)
		{
			std::cout << name << " not found in table." << std::endl;
		}

		// - match is found
		else 
		{
			delPtr = Ptr1;
			Ptr1 = Ptr1->next;
			Ptr2->next = Ptr1;
			delete delPtr;

			std::cout << name << " was removed." << std::endl;
		}
	}
}

int hashtable::IndexCount(int index)
{
	int count = 0;

	if (HashTable[index]->name == "empty")
	{
		return count;
	}
	else
	{
		count++;
		item* Ptr = HashTable[index];
		while (Ptr->next != NULL)
		{
			count++;
			Ptr = Ptr->next;
		}
	}
	return count;
}

void hashtable::PrintTable()
{
	int number;
	for (int i = 0; i < tableSize; i++) 
	{
		number = IndexCount(i);
		std::cout << "/------------------------\\" << std::endl;
		std::cout << "index = " << i << std::endl;
		std::cout << HashTable[i]->name << " - " << HashTable[i]->goal << std::endl;
		std::cout << "buckets # of items = " << number << std::endl;
		std::cout << "\\------------------------/" << std::endl;
	}
}

void hashtable::PrintIndexItems(int index)
{
	item* Ptr = HashTable[index];
	if (Ptr->name == "empty")
	{
		std::cout << " - // bucket #" << index << " is empty.\n";
	}
	else 
	{
		std::cout << "index #" << index << " contains:\n";
		while (Ptr != NULL)
		{
			std::cout << "||------------------------||" << std::endl;
			std::cout << Ptr->name << " - " << Ptr->goal << std::endl;
			std::cout << "||------------------------||" << std::endl;
			Ptr = Ptr->next;
		}
			
	}
}

void hashtable::FindGoal(std::string name)
{
	int index = Hash(name);
	bool foundName = false;
	std::string goal;
	
	item* Ptr = HashTable[index];
	while (Ptr != NULL) 
	{
		if (Ptr->name == name)
		{
			foundName = true;
			goal = Ptr->goal;
		}
		Ptr = Ptr->next;
	}
	if (foundName == true)
	{
		std::cout << name << " - " << goal << "\n" << std::endl;
	}
	else
	{
		std::cout << name << " not found in table.\n" << std::endl;
	}
}
