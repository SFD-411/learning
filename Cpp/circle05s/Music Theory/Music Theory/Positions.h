#pragma once

// alphanumeric representation of interval spacings
enum ePos { P1, m2, M2, m3, M3, P4, TT, P5, m6, M6, m7, M7, P8 };
const std::vector<std::string> INTERVAL = { "P1", "m2", "M2", "m3", "M3", "P4", "TT", "P5", "m6", "M6", "m7", "M7", "P8" };
// naming conventions 
struct intervals
{
	std::map<std::string, std::string> DEGREE_INTERVAL = { {"Tonic", "P1" },{ "Super-Tonic", "M2" },
		{"Mediant", "M3"},{"Sub-Dominant", "P4"},{"Dominant", "P5"},{ "Sub-Mediant", "M6" },{ "Leading Tone", "M7"} };
	std::map<std::string, std::string> DEGREE_MODE = { {"Tonic", "Ionian"}, {"Super-Tonic", "Dorian"}, {"Mediant","Phrygian"},
{"Sub-Dominant", "Lydian"},{"Dominant", "Mixolydian"},{"Sub-Mediant", "Aeolian"},{"Leading Tone", "Locrian"} };
	const std::vector<std::string> DEGREE = { "Tonic", "Super-Tonic", "Mediant", "Sub-Dominant", "Dominant", "Sub-Mediant", "Leading Tone" };
	const std::vector<std::string> VALUE = { "I", "ii", "iii", "IV", "V", "vi", "vii*" };
	const std::vector<std::string> MODE = { "Ionian", "Dorian", "Phrygian", "Lydian", "Mixolydian", "Aeolian", "Locrian" };
	const std::map<std::string, int> mPOS = { {INTERVAL[P1], P1 }, {INTERVAL[m2], m2}, {INTERVAL[M2],M2}, {INTERVAL[m3], m3}, {INTERVAL[M3],M3},
	{INTERVAL[P4], P4}, {INTERVAL[TT], TT},{INTERVAL[P5], P5}, {INTERVAL[m6],m6}, {INTERVAL[M6],M6}, {INTERVAL[m7], m7}, {INTERVAL[M7], M7}, {INTERVAL[P8], P8} };
};

