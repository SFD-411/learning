#include <iostream>	
#include <map>
#include <sstream>
#include <string>
#include <vector>
#include "NoteLibrary.h"
#include "Primary.h"



int main()
{
	notes note;
	note.fifths();

	intervals modes;



	// making it so the notes dont matter
	for (int i = 0; i < P5; i++)
	{
		std::cout << " " << i << "\t" << modes.VALUE[i] << "\t" << modes.MODE[i] << "    \t" << modes.DEGREE[i] << "\n";
	}

	// output notes from the third and fifth of each key
	for (int i = 0; i < P8; i++)
	{
		for (auto j : note.modulator(note.Key[i].mode_numerals))
		{
			std::cout << j << " ";
		}
		std::cout << std::endl;

	}
		return 0;
}