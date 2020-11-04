#include "Primary.h"

void printCircle()
{
	notes note; // instantiates the notes class
	note.fifths(); // populates the circle of fifths struct

	std::cout << "	-	Circle of Fifths Struct	 -	" << "\n" << "  Tonic \t Diminished Scale " << "\n\t\t";
	for (auto f : note.intervals.Numerals)
	{
		std::cout << f << "\t";
	}
	std::cout << std::endl;;

	for (int i = 0; i < P8; i++)
	{
		// shows index number, and key position
		std::cout << " " << i << " " << note.Key[i].Posit << "\t\t";

		// outputes the scale, based on the numeric representation of the literal name of each individual mode
		for (auto f : note.intervals.modeName)
		{
			std::cout << note.Key[i].Modes[f] << "\t";
		}
		std::cout << std::endl;

		// same thing as above for when a scale has an enharmonic parallel
		if (note.Key[i].Enharmonic.size() > M2)
		{
			std::cout << " - enharmonic - ";
			for (auto f : note.intervals.modeName)
			{
				std::cout << note.Key[i].enhModes[f] << "\t";
			}
			std::cout <<  std::endl;
		}
	}
}

int main()
{
	printCircle();
	
	return 0;
}