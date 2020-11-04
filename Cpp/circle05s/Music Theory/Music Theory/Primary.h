#pragma once

#include <iostream>
#include <map>
#include <string>
#include <sstream>
#include <vector>
#include "Positions.h"



// stores all the keys scale information
struct circleOFifth
{
	std::string root_position;
	std::string root;
	std::string root_enharmonic;
	std::vector<std::string> scale;
	std::vector<std::string> scale_enharmonic;
	std::vector<std::string> chord; 
	std::vector<std::string> chord_enharmonic;
	std::map<std::string, std::string> mode_numerals;
	std::map<std::string, std::string> mode_enharmonic;
};

// finds the notes and modes for all the keys
class notes
{
public:
	circleOFifth Key[P8];
	intervals modes;
	const void fifths();  // TODO seperate bools and vector assignment
	const std::vector<std::string> modulator(std::map<std::string, std::string>);

private:
	//  - Save - 
	bool isFlat = false;
	bool isFlatEnharmonic = false;
	bool isSharp = false;
	bool isSharpEnharmonic = false;
	const std::vector<int> majPos = { P1, M2, M3, P4, P5, M6, M7 };
	const std::vector<int> dimPos = { P1, m2, m3, P4, TT, m6, m7 };
	const std::vector<int> minPos = { P1, m2, m3, P4, TT, m6, m7 }; 
	//  - Save - 

	std::vector<std::string> triad; // returns harmonys
	const std::vector<std::string> sharps{ "C","C#","D","D#","E","F","F#","G","G#","A","A#","B" };; //x
	const std::vector<std::string> dblSharps{ "B#","C#","D","D#","E","E#","F#","F##","G#","A","A#","B" }; //x
	const std::vector<std::string> flats{ "C","Db","D","Eb","E","F","Gb","G","Ab","A","Bb","B" }; //x
	const std::vector<std::string> dblFlats{ "C","Db","D","Eb","Fb","F","Gb","G","Ab","Bbb","Bb","Cb" }; //x
};