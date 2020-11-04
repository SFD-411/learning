#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "Harmonies.h"

int main()
{
	notes stuff;
	index index[P5];
	intervals data;

	std::cout << " major ";
	for (auto i : stuff.majPos)
	{
		std::cout << stuff.sharps[i] << " " ;
	}
	std::cout << "\n" << " minor ";
	for (auto i : stuff.minPos)
	{
		std::cout << stuff.sharps[(M6 + i) % P8] << " ";
	}
	std::cout << "\n" << " dim ";
	for (auto i : stuff.dimPos)
	{
		std::cout  << stuff.sharps[(M7 + i) % P8] << " ";
	}
	std::cout << "\n" << std::endl;

	for (auto note : data.DEGREE)
	{
		std::cout << note << "\n" << data.DEGREE_POSITION[note] << " " << data.DEGREE_MODE[note] << "\n\n";
	}

	return 0;
}
//
//std::vector<std::string> mode_changer()
//{
//	return;
//}