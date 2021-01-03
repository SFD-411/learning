#pragma
#include "Primary.h"

// populates the notes for the circle of fifths struct
const void notes::fifths()
{
int note_count = P1;
for (int i = 0; i < P8; i++)
{
	bool unison = true; // reset unison 

	// 0 - 3 sharps : 4 - 6 sharps and doubleflats : 6 double sharps and double flats : 7 - 8 flats and double sharp :
	if (i < TT) { isSharp = true; }
	else if (i > TT) { isFlat = true; isFlatEnharmonic = false; }
	else {
		isSharp = false;
		isSharpEnharmonic = true;
	}
	if (i < P5 && i > m3) { isFlatEnharmonic = true; }
	else if (i == M6) { isSharpEnharmonic = false; }


	// assigns invidiual root note and interval position once
	while (unison)
	{
		Key[i].Posit = pos[note_count];
		if (isSharp) Key[i].Root = (sharps[note_count]);
		else if (isFlat) Key[i].Root = (flats[note_count]);
		else Key[i].Root = (dblSharps[note_count]);
		if (isFlatEnharmonic) Key[i].enhRoot = (dblFlats[note_count]);
		else if (isSharpEnharmonic) Key[i].enhRoot = (dblSharps[note_count]);
		unison = false;
	}

	// iterates scales based on note_count position and major scale incriments
	for (auto j : majPos)
	{
		if (isSharp)	Key[i].Scale.push_back(sharps[(note_count + j) % P8]);
		else if (isFlat) 	Key[i].Scale.push_back(flats[(note_count + j) % P8]);
		else Key[i].Scale.push_back(dblSharps[(note_count + j) % P8]);
		if (isFlatEnharmonic) 	Key[i].Enharmonic.push_back(dblFlats[(note_count + j) % P8]);
		else if (isSharpEnharmonic)	Key[i].Enharmonic.push_back(dblSharps[(note_count + j) % P8]);
	}

	// match scale to interval numeral
	for (int k = 0; k < Key[i].Scale.size(); k++)
	{
		Key[i].Modes.insert(std::make_pair(intervals.modeName[k], Key[i].Scale[k]));

		if (isSharpEnharmonic || isFlatEnharmonic)
			Key[i].enhModes.insert(std::make_pair(intervals.modeName[k], Key[i].Enharmonic[k]));
	}
	note_count = (note_count + P5) % P8; // change fifth
}
}

// finds the mode in a given scale
const std::vector<std::string> notes::modulator(std::map<std::string, std::string> module)
{
	triad.clear();

	// iterates through interval names to return the 1 3 5 a given scale
	for (int i = P1; i < m3; i++)
	{
		std::string tri = "";
		switch (i)
		{
		case 0: 
			tri = intervals.Numerals[P1]; // "I"
			break;
		case 1: 
			tri = intervals.Numerals[M2]; // "iii"
			break;
		case 2: 
			tri = intervals.Numerals[M3]; // "V"
			break;
		}
		triad.push_back(module[tri]);
	}
	return triad;
}
