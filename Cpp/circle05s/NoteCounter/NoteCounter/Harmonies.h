#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <map>

// alphanumeric representation of interval spacings
enum ePos { P1, m2, M2, m3, M3, P4, TT, P5, m6, M6, m7, M7, P8 };

// naming conventions 
struct intervals
{
	std::map<std::string, std::string> DEGREE_POSITION = { {"Tonic", "P1" },{ "Super-Tonic", "M2" },
		{"Mediant", "M3"},{"Sub-Dominant", "P4"},{"Dominant", "P5"},{ "Sub-Mediant", "M6" },{ "Leading Tone", "M7"} };
	std::map<std::string, std::string> DEGREE_MODE = { {"Tonic", "Ionian"}, {"Super-Tonic", "Dorian"}, {"Mediant","Phrygian"},
{"Sub-Dominant", "Lydian"},{"Dominant", "Mixolydian"},{"Sub-Mediant", "Aeolian"},{"Leading Tone", "Locrian"} };
	const std::vector<std::string> DEGREE = { "Tonic", "Super-Tonic", "Mediant", "Sub-Dominant", "Dominant", "Sub-Mediant", "Leading Tone" };
	const std::vector<std::string> VALUE = { "I", "ii", "iii", "IV", "V", "vi", "vii*" };
	const std::vector<std::string> MODE = { "Ionian", "Dorian", "Phrygian", "Lydian", "Mixolydian", "Aeolian", "Locrian" };
	const std::map<std::string, int> mPOS = { {INTERVAL[P1], P1 }, {INTERVAL[m2], m2}, {INTERVAL[M2],M2}, {INTERVAL[m3], m3}, {INTERVAL[M3],M3},
	{INTERVAL[P4], P4}, {INTERVAL[TT], TT},{INTERVAL[P5], P5}, {INTERVAL[m6],m6}, {INTERVAL[M6],M6}, {INTERVAL[m7], m7}, {INTERVAL[M7], M7}, {INTERVAL[P8], P8} };
};

struct index
{
	const std::vector<std::string> INTERVAL = { "P1", "m2", "M2", "m3", "M3", "P4", "TT", "P5", "m6", "M6", "m7", "M7", "P8" }; // position name for enum 
	std::string root; // note in scale
	std::string mode; // position mode name
	std::string value; // numeral
 	std::string degree; // position value
	std::vector<std::string> scale; // stores the scale
	std::vector<std::string> chord; // stores the triad
	
}; // table data

// almost useless - temporary jumper
struct notes
{
	const std::vector<std::string> sharps{ "C","C#","D","D#","E","F","F#","G","G#","A","A#","B" };;
	const std::vector<std::string> dblSharps{ "B#","C#","D","D#","E","E#","F#","F##","G#","A","A#","B" };
	const std::vector<std::string> flats{ "C","Db","D","Eb","E","F","Gb","G","Ab","A","Bb","B" };
	const std::vector<std::string> dblFlats{ "C","Db","D","Eb","Fb","F","Gb","G","Ab","Bbb","Bb","Cb" };
	// - save
	const std::vector<int> majPos = { P1, M2, M3, P4, P5, M6, M7 };
	const std::vector<int> minPos = { P1, M2, m3, P4, P5, m6, m7 };
	const std::vector<int> dimPos = { P1, m2, m3, P4, TT, m6, m7 };
	// - save

};