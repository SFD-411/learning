#include <cstdlib>
#include <iostream>
#include <string>
#include "hash.h"

int main() 
{
	hashtable ht;
	std::string name = "";
	ht.AddItem("Richard", "Music");
	ht.AddItem("Javid", "Teaching");
	ht.AddItem("Discord", "Fun");
	ht.AddItem("SoulFilledDirt", "Bliss");
	ht.AddItem("Isaac", "Discipline");
	ht.AddItem("Elaine", "Ruth");

	ht.PrintTable();
	std::cout << std::endl;

	while (name != "exit")
	{
		std::cout << "\nRemove item : ";
		std::cin >> name;
		if (name != "exit");
			ht.RemoveItem(name);
		std::cout << std::endl;
		for (int i = 0; i < 4; i++)
			ht.PrintIndexItems(i);
	}

	ht.PrintTable();
	return 0;
}