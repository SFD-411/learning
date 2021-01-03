#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <cmath>
#include <iterator>
#include <map>

const std::vector<std::string> Sharps{ "C","C#","D","D#","E","F","F#","G","G#","A","A#","B" };
const std::vector<std::string> dblSharps{ "B#","C#","D","D#","E","E#","F#","F##","G#","A","A#","B" };
const std::vector<std::string> Flats{ "C","Db","D","Eb","E","F","Gb","G","Ab","A","Bb","B" };
const std::vector<std::string> dblFlats{ "C","Db","D","Eb","Fb","F","Gb","G","Ab","Bbb","Bb","Cb" };
const std::vector<std::string> pos{ "P1", "m2", "M2", "m3", "M3", "P4", "TT", "P5", "m6", "M6", "m7", "M7", "P8" };
enum intervals { P1, m2, M2, m3, M3, P4, TT, P5, m6, M6, m7, M7, P8 };
static std::map<std::string, int> eDeg = { {pos[P1], P1 }, {pos[m2], m2}, {pos[M2],M2}, {pos[m3], m3}, {pos[M3],M3},
{pos[P4], P4}, {pos[TT], TT},{pos[P5], P5}, {pos[m6],m6}, {pos[M6],M6}, {pos[m7], m7}, {pos[M7], M7}, {pos[P8], P8} };

// arranges positions of base circle
// returns note positions of fifths from enum iteration
inline std::vector<std::string> fifthCircle_Intervals()
{
	std::vector<std::string> temp;
	int maj = P1;
	int min = M6;
	int dim = M7;
	int note_5 = 0;

	// store notes of fifths intervals based on ring
	for (int i = 0; i < m3; i++)
	{
		int reset = P1; 
		int ring = i;
		
		switch (ring)
		{
		case 0:
			ring = maj;
			break;
		case 1:
			ring = min;
			break;
		case 2:
			ring = dim;
			break;
		}

		note_5 = ring;

		do {
			temp.push_back(pos[note_5]); // push letter notation
			note_5 = ((note_5 + P5) % P8); // iterates through 5th positions
			reset++;
		} while (reset < P8);
	}
		return temp; 
}

// strings fifths based on fifths intervals sequence
static inline std::vector<std::string> iter_5()
{
	std::vector<std::string> fifths;
	bool isFlat = false;
	bool isSharp = false;
	
	// returns note positions of fifths from enum iteration
	const std::vector<std::string> iterations = fifthCircle_Intervals();
	for (int i = 0; i < m3; i++)
	{
		for (int j = 0; j < P8; j++)
		{
			int ringer = (i * P8) + j;

			if (iterations[j] == pos[TT] && !isFlat)
			{
				// finds doubles at TT followed by flats
				fifths.push_back(dblSharps[eDeg[iterations[ringer]]]);
				isFlat = true; 	isSharp = false;
			}
			else if (!isFlat || isSharp)
				fifths.push_back(Sharps[eDeg[iterations[ringer]]]);
			else if (isFlat)
			{
				fifths.push_back(Flats[eDeg[iterations[ringer]]]);
				// sharps starts after P4
				if (iterations[j] == pos[P4]) 	{	isSharp = true; isFlat = false;	}
			}
		}
	}
	return fifths;
}

// =======	 circle to square =======
struct vec3
{
	double circ;
	double x;
	double y;
	int vecloc;
};
class display
{
public:
	void square(std::vector<std::string>);
	void circle();

private:
	vec3 v[36];
	bool vecfind(int row, int col);
	int vecount = 0;
	double r = 6.75;
	double pi = 3.141;
};