#include <iostream>
#include <map>
#include <string>
#include <sstream>
#include <vector>
#include "Positions.h"

void SetNotes(notes, noteindex);
void PrintMain(notes, noteindex);

int main()
{
	notes notes; // instatiates note class
	noteindex index;

	// input for note class
	const std::vector<std::string> C_Major = { "C", "D", "E", "F", "G", "A", "B" };

	// calculates scales for all keys
	notes.populateKeys(C_Major);

	// temp -- needs embedded into class constructor
		//	----  sets Degrees for each scale --
		notes.scaleDegrees(notes.root.scale, 0);

		// sets sharp keys scale degrees
		notes.isSharp = true;
		for (int i = 0; i < 8; i++)
		{
			notes.scaleDegrees(notes.sharps[i].scale, i);
		}
		notes.isSharp = false;

		// sets flat keys scale degrees
		notes.isFlat = true;
		for (int i = 0; i < 8; i++)
		{
			notes.scaleDegrees(notes.flats[i].scale, i);
		}
		notes.isFlat = false;

	SetNotes(notes, index);
	PrintMain(notes, index);

	return 0;
}

// initializes note table values
void SetNotes(notes notes, noteindex index)
{
	// C Major
	index.NotePosition(notes.root.root, notes.root.position, notes.posNumber(notes.root.position));

	// sharps and flats
	for (int count = 0; count < 8; count++)
	{
		index.NotePosition(notes.sharps[count].root, notes.sharps[count].position, notes.posNumber(notes.sharps[count].position));
		index.NotePosition(notes.flats[count].root, notes.flats[count].position, notes.posNumber(notes.flats[count].position));
	}

	return;
}

// outputs degrees, and associated scales per individual key.
void PrintMain(notes notes, noteindex index) 
{
	for (int i = 0; i < 12; i++)
	{
		index.PrintIndices(i);
	}
	
	//std::cout << "index \t\tscale\n\t";
	//std::cout << "      ";
	//
	//for (auto i : DEGREE) // prints degree names
	//{
	//	std::cout << i << " ";
	//}

	//// prints C Key
	//std::cout << "\n0  " << notes.root.position << "\t\t";
	//for (auto degree : DEGREE)
	//{
	//	std::cout << notes.root.degree_scale[degree] << "\t";
	//}

	//// prints fifths keys and scales by degrees
	//std::cout << "\n  Fifths" << std::endl;
	//for (int index = 0; index < 8; index++)
	//{
	//	std::cout << index << "  " << notes.sharps[index].position << " " << "\t\t";
	//	for (auto degree : DEGREE) { std::cout << notes.sharps[index].degree_scale[degree] << "\t"; }
	//	std::cout << std::endl;
	//}
	//std::cout << std::endl;

	//// prints fourths keys and scales by degrees
	//std::cout << "\n  Fourths" << std::endl;
	//for (int index = 0; index < 8; index++)
	//{
	//	std::cout << index << "  " << notes.flats[index].position << "\t\t";
	//	for (auto degree : DEGREE) { std::cout << notes.flats[index].degree_scale[degree] << "\t"; }
	//	std::cout << std::endl;
	//}
}