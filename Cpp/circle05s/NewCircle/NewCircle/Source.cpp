#include "Circle.h"

display screen;

int main()
{
	std::cout << " :: intervals :: " << std::endl;
	// finds chromatic intervals
	for (int i = 0; i < P8; i++)
	{
		//  string from vec
		std::cout << pos[i] + "-"; 
		// string from enum taking string from vec
		std::cout << Flats[eDeg[pos[i]]] << ", "; 
	}

	std::cout << "\n" << std::endl;
	
	std::cout << " Circle of Fifths " << std::endl;
	screen.circle();
	screen.square(iter_5());

	return 0;
}
