#pragma
#include "Primary.h"

// populates the notes for the circle of fifths struct
const void notes::fifths()
{
int fifth = M7;
for (int i = 0; i < P8; i++)
{
	bool unison = true; // reset unison 

	
	//  - Save - 
	// 0 - 3 sharps : 4 - 6 sharps and doubleflats : 6 double sharps and double flats : 7 - 8 flats and double sharp :
	if (i < TT) { isSharp = true; }
	else if (i > TT) { isFlat = true; isFlatEnharmonic = false; }
	else {
		isSharp = false;
		isSharpEnharmonic = true;
	}
	if (i < P5 && i > m3) { isFlatEnharmonic = true; }
	else if (i == M6) { isSharpEnharmonic = false; }
	//  - Save - 

	// assigns invidiual root note and interval INTERVAL once
	while (unison)
	{
		Key[i].root_position = INTERVAL[fifth];
		if (isSharp) Key[i].root = (sharps[fifth]);
		else if (isFlat) Key[i].root = (flats[fifth]);
		else Key[i].root = (dblSharps[fifth]);
		if (isFlatEnharmonic) Key[i].root_enharmonic = (dblFlats[fifth]);
		else if (isSharpEnharmonic) Key[i].root_enharmonic = (dblSharps[fifth]);
		unison = false;
	}

	// iterates scales based on fifth INTERVAL and major scale incriments
	for (auto j : dimPos)
	{
		if (isSharp)	Key[i].scale.push_back(sharps[(fifth + j) % P8]);
		else if (isFlat) 	Key[i].scale.push_back(flats[(fifth + j) % P8]);
		else Key[i].scale.push_back(dblSharps[(fifth + j) % P8]);
		if (isFlatEnharmonic) 	Key[i].scale_enharmonic.push_back(dblFlats[(fifth + j) % P8]);
		else if (isSharpEnharmonic)	Key[i].scale_enharmonic.push_back(dblSharps[(fifth + j) % P8]);
	}

	// match scale to interval numeral
	for (int k = 0; k < Key[i].scale.size(); k++)
	{
		Key[i].mode_numerals.insert(std::make_pair(modes.MODE[k], Key[i].scale[k]));

		if (isSharpEnharmonic || isFlatEnharmonic)
			Key[i].mode_enharmonic.insert(std::make_pair(modes.MODE[k], Key[i].scale_enharmonic[k]));
	}
	fifth = (fifth + P5) % P8; // change fifth
}
}


// --  - Save -   --
//
// finds the mode in a given scale
const std::vector<std::string> notes::modulator(std::map<std::string, std::string> module)
{
	triad.clear();

	// iterates through interval names to return the 1 3 5 chord a given scale
	for (int i = P1; i < m3; i++)
	{
		std::string tri = "";
		switch (i)
		{
		case 0: 
			tri = modes.MODE[P1]; // "I"  -- TODO Needs to take DEGREE 
			break;
		case 1: 
			tri = modes.MODE[M2]; // "iii" -- TODO Needs to take DEGREE 
			break;
		case 2: 
			tri = modes.MODE[M3]; // "V" -- TODO Needs to take DEGREE 
			break;
		}
		triad.push_back(module[tri]); // TODO use pointer to return value
	}
	return triad;
}
//
//  - Save - 
//