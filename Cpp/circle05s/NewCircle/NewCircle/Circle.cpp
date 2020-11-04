#include "Circle.h"

bool display::vecfind(int row, int col)
{
	for (int i = 0; i < 36; i++) {
		if (v[i].x >= col && v[i].x < col + 1 && v[i].y >= row && v[i].y < row + 1)
		{
			v[vecount].vecloc = i;
			return true;
		}
	}
	return false;
}

void display::square(std::vector<std::string> notes)
{
	for (int row = 0; row < 23; row++) {
		for (int col = 0; col < 43; col++) {
			if (vecfind(row, col))
			{
				int shit = v[vecount].vecloc;
				vecount++;
				std::cout << notes[shit];
			}
			else { std::cout << " "; }
		}
		std::cout << std::endl;
	}
	return;
}

void display::circle()
{
	for (int i = 0; i < 3; i++) {
		v[i].circ = (2 * pi)*r;
		for (int j = 0; j < 12; j++) {
			int t = 21;
			int u = 12;
			int comp = j * 30 + 270 % 360;
			double rad = comp * (pi / 180);
			double x = t + (r * cos(rad)) * 11 / 6;
			double y = u + (r * sin(rad));
			int fact = i * 12 + j;
			v[fact].x = x;
			v[fact].y = y;
		}
		r += 2;
	}
}
