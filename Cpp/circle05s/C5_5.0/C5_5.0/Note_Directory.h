#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <cmath>
#include <iterator>
#include <map>


const std::vector<std::string> sharps{ "C","C#","D","D#","E","F","F#","G","G#","A","A#","B" };
const std::vector<std::string> sharps_double{ "B#","C#","D","D#","E","E#","F#","F##","G#","A","A#","B" };
const std::vector<std::string> flats{ "C","Db","D","Eb","E","F","Gb","G","Ab","A","Bb","B" };
const std::vector<std::string> flats_double{ "C","Db","D","Eb","Fb","F","Gb","G","Ab","Bbb","Bb","Cb" };
enum intervals { P1, m2, M2, m3, M3, P4, TT, P5, m6, M6, m7, M7, P8 };

// give me 3 circles
	// check which scale based on root note
		// F#, C# or G# is double sharps
		// Gb, Cb, or Fb is double flats
		// A, B, D, E, G are sharp
		// Ab, Bb, Db, Eb, F are flat
	// are the notes in the scale?
		// if not, which notes are they?
			// inner circle has majors
			// middle circle has minors
			// outter circle has diminished


class notation
{
public:


private:
	const std::vector<std::string> pos{ "P1", "m2", "M2", "m3", "M3", "P4", "TT", "P5", "m6", "M6", "m7", "M7", "P8" };
	const std::vector<int> Major = { P1, M2, M3, P4, P5, M6, M7, P8 };
};

// VVV making the circle VVV
/*
struct coord
{
	double circ;
	double x;
	double y;
	int vecloc;
} v[36];

int vecord = 0;
int root = 0;
struct steps { int maj = 0; int min = 0; } step;

const int size = flats.size();

class display
{
public:
	bool vecfind(int row, int col) {
		for (int i = 0; i < 36; i++) {
			if (v[i].x >= col && v[i].x < col + 1 && v[i].y >= row && v[i].y < row + 1)
			{
				v[vecord].vecloc = i;
				vecord += 1;
				return true;
			}
		}
		return false;
	}

	void square() {
		for (int row = 0; row < 23; row++) {
			for (int col = 0; col < 39; col++) {
				if (vecfind(row, col))
				{
					vecount += 1;
					std::cout << vecount;
				}
				else { std::cout << " "; }
			}
			std::cout << std::endl;
		}
		return;
	}

private:
	int vecount = 0;
	int varcount = 0;

	void circle() {
	double pi = 3.141;
	double r = 6.75;
	for (int i = 0; i < 3; i++) {
		v[i].circ = (2 * pi)*r;
		for (int j = 0; j < 12; j++) {
			int t = 21;
			int u = 12;
			int comp = j * 30 + 270 % 360;
			double rad = comp * (pi / 180);
			double x = t + (r * cos(rad)) * 11/6;
			double y = u + (r * sin(rad));
			int fact = i * 12 + j;
			v[fact].x = x;
			v[fact].y = y;
		}
		r += 2;
	}
}
};*/