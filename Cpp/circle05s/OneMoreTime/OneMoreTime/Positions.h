#pragma once

#include <iostream>
#include <map>
#include <string>
#include <sstream>
#include <vector>
#include "NoteTable.h"

const std::vector<std::string> DEGREE = { "Tonic", "SuperTonic", "Mediant", "Sub-Dom", "Dominant", "Sub-Med", "Leading Tone" };

// stores all the scales to all the keys
struct keys
{
	std::string position; // stores position per P1-P8
	std::string root; // stores root note of key
	std::vector<std::string> scale; // stores scale of key
	std::map < std::string, std::string > scale_degree; // sets keys map of degrees:scale
	std::map < std::string, std::string > degree_scale; // sets keys maps of degrees:scale
};

// performs initial population of all keys, scales, and degrees
class notes
{
public:
	int posNumber(std::string);
	bool isSharp = false;
	bool isFlat = false;
	keys root, sharps[8], flats[8];
	void populateKeys(std::vector<std::string> scale); // Sets Root, Sharp and Flat keys
	void scaleDegrees(std::vector<std::string> scale, int key); // maps Degree to Scale
	
private:
	enum ePos { P1, m2, M2, m3, M3, P4, TT, P5, m6, M6, m7, M7, P8 };
	const std::vector<std::string> POSITION = { "P1", "m2", "M2", "m3", "M3", "P4", "TT", "P5", "m6", "M6", "m7", "M7", "P8" };
	std::map<std::string, int> PositionNUM = { {"P1", P1 }, { "m2" , m2 }, { "M2" , M2 }, { "m3" , m3 }, { "M3" , M3 },
		{ "P4" , P4 }, { "TT" , TT },	{ "P5" , P5 }, { "m6" , m6 }, { "M6" , M6 }, { "m7" , m7 },{"M7" , M7 }, { "P8", P8 } };
	int prev = 0;
	int fifth = 0;
	int fourth = 0;
	int notecount = 0;
};