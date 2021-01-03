#pragma once

#include <iostream>
#include <map>
#include <string>
#include <sstream>
#include <vector>

// alphanumeric representation of interval spacings
enum positions { P1, m2, M2, m3, M3, P4, TT, P5, m6, M6, m7, M7, P8 };
const std::vector<std::string> pos = { "P1", "m2", "M2", "m3", "M3", "P4", "TT", "P5", "m6", "M6", "m7", "M7", "P8" };
const std::map<std::string, int> eDeg = { {pos[P1], P1 }, {pos[m2], m2}, {pos[M2],M2}, {pos[m3], m3}, {pos[M3],M3},
	{pos[P4], P4}, {pos[TT], TT},{pos[P5], P5}, {pos[m6],m6}, {pos[M6],M6}, {pos[m7], m7}, {pos[M7], M7}, {pos[P8], P8} };

// acts as iterators for interval naming conventions
struct intervals
{
	const std::vector<std::string> Numerals = { "I", "ii", "iii", "IV", "V", "vi", "vii°" };
	const std::vector<std::string> modeName = { "Ionian", "Dorian", "Phrygian", "Lydian", "Mixolydian", "Aeolian", "Locrian" };
	std::map<std::string, std::string> modeMap = { {"Ionian", "I"}, {"Dorian", "ii"}, {"Phrygian", "iii"}, 
	{ "Lydian", "IV"},{ "Mixolydian", "V"},{"Aeolian", "vi"},{"Locrian","vii°"} };
};

// stores all the keys scaling information
struct circleOFifth
{
	std::string Posit;
	std::string Root;
	std::string enhRoot;
	std::vector<std::string> Scale;
	std::vector<std::string> Enharmonic;
	std::vector<std::string> Harmonies;
	std::vector<std::string> enhHarmonies;
	std::map<std::string, std::string> Modes;
	std::map<std::string, std::string> enhModes;
};

// finds the notes and intervals for all the keys
class notes
{
public:
	circleOFifth Key[P8];
	intervals intervals;
	const void fifths();  // TODO seperate bools and vector assignment
	const std::vector<std::string> modulator(std::map<std::string, std::string>);

private:
	bool isFlat = false;
	bool isFlatEnharmonic = false;
	bool isSharp = false;
	bool isSharpEnharmonic = false;
	std::vector<std::string> triad;
	const std::vector<std::string> sharps{ "C","C#","D","D#","E","F","F#","G","G#","A","A#","B" };;
	const std::vector<std::string> dblSharps{ "B#","C#","D","D#","E","E#","F#","F##","G#","A","A#","B" };
	const std::vector<std::string> flats{ "C","Db","D","Eb","E","F","Gb","G","Ab","A","Bb","B" };
	const std::vector<std::string> dblFlats{ "C","Db","D","Eb","Fb","F","Gb","G","Ab","Bbb","Bb","Cb" };
	const std::vector<int> majPos = { P1, M2, M3, P4, P5, M6, M7 };
	const std::vector<int> dimPos = { P1, m2, m3, P4, TT, m6, m7 };
	const std::vector<int> minPos = { P1, m2, m3, P4, TT, m6, m7 };
};