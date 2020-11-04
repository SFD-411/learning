#include <algorithm>
#include <cmath>
#include <ctime>
#include <iostream>
#include <iterator>
#include <map>
#include <string>
#include <sstream>
#include <vector>

int vecord = 0;
double pi = 3.14159;
double radcal = pi / 180;
double hr = 5.15;
double mr = 8.75;

// circle points for numerals
struct coord
{
	double circ;
	double x;
	double y;
	int vecloc;
} v[36];

// time struct for local and greenwich time
struct clock
{
	int hour;
	int min;
	int year;
	int month;
	int day;
} yt, gt;

struct vectime
{
	double x;
	double y;
} g[6], l[6], m[9], tu;

struct timedeg
{
	double hdeg;
	double mdeg;
} gmt, lmt, mht;

void timestruct()
{
	std::time_t t = std::time(0);
	std::tm *loc = std::localtime(&t);

	yt.year = (loc->tm_year + 1900);
	yt.month = (loc->tm_mon + 1);
	yt.day = loc->tm_mday;
	yt.hour = loc->tm_hour % 12;
	yt.min = loc->tm_min;
	lmt.mdeg = (double(yt.min) * 6);
	double madd = (double(yt.min) / 60);
	lmt.hdeg = (double((yt.hour + madd) * 30));

	std::tm *gm = std::gmtime(&t);
	gt.year = (gm->tm_year + 1900);
	gt.month = (gm->tm_mon + 1);
	gt.day = gm->tm_mday;
	gt.hour = gm->tm_hour % 12;
	gt.min = gm->tm_min;
	gmt.hdeg = (double((gt.hour + madd) * 30));
}

void minutes()
{
	int compm = lmt.mdeg + 270 % 360;
	double mrad = compm * pi / 180;

	for (int mi = 0; mi < mr;)
	{
		double mx = tu.x + double((mi + 1) * cos(mrad)) * 5 / 3;
		double my = tu.y + double((mi + 1) * sin(mrad));
		m[mi].x = mx;
		m[mi].y = my;
		mi++;
	}
}

void ghours()
{
	int gcomphr = gmt.hdeg + 270 % 360;
	double grad = gcomphr * (pi / 180);

	for (int gi = 0; gi < hr;)
	{
		double gx = tu.x + double((gi + 1) * cos(grad)) * 5 / 3;
		double gy = tu.y + double((gi + 1) * sin(grad));
		g[gi].x = gx;
		g[gi].y = gy;
		gi += 1;
	}
}

void lhours()
{
	int lcomph = lmt.hdeg + 270 % 360;
	double lrad = lcomph * (pi / 180);

	for (int li = 0; li < hr;)
	{
		double yx = tu.x + double((li + 1) * cos(lrad)) * 5 / 3;
		double yy = tu.y + double((li + 1) * sin(lrad));
		l[li].x = yx;
		l[li].y = yy;
		li += 1;
	}
}

bool vecfind(int row, int col)
{
	for (int i = 0; i < 12; i++)
	{
		if (v[i].x >= col && v[i].x < col + 1 && v[i].y >= row && v[i].y < row + 1)
		{
			v[vecord].vecloc = i + 1;
			vecord += 1;
			return true;
		}
	}
	return false;
}

bool ghand = false;
bool lhand = false;
bool mhand = false;

bool hhandfind(int row, int col)
{
	for (int hi = 0; hi < hr; hi++)
	{
		if (g[hi].x >= col && g[hi].x < col + 1 && g[hi].y >= row && g[hi].y < row + 1)
		{
			ghand = true;
			return true;
		}
		else if (l[hi].x >= col && l[hi].x < col + 1 && l[hi].y >= row && l[hi].y < row + 1)
		{
			lhand = true;
			return true;
		}
	}
	ghand = false;
	lhand = false;
	return false;
}


bool mhandfind(int row, int col)
{
	for (int mi = 0; mi < mr; mi++)
	{
		if (m[mi].x >= col && m[mi].x < col + 1 && m[mi].y >= row && m[mi].y < row + 1)
		{
			return true;
		}
	}
	return false;
}

// find circle points
void circle()
{
	double r = 10.75;
	for (int j = 0; j < 12; j++)
	{
		int comp = (((j + 1) * 30) + 270) % 360;
		double rad = comp * pi / 180;
		double x = tu.x + (r * cos(rad)) * 5 / 3;
		double y = tu.y + (r * sin(rad));
		v[j].x = x;
		v[j].y = y;
	}
}

void square()
{
	int vecount = 0;
	int varcount = 0;
	for (int row = 0; row < 23; row++)
	{
		for (int col = 0; col < 39; col++)
		{
			if (vecfind(row, col))
			{
				varcount = v[vecount].vecloc;
				std::cout << varcount;
				vecount += 1;
			}
			else if (tu.x == col && tu.y == row)
			{
				std::cout << "O";
			}
			else if (hhandfind(row, col))
			{
				if (ghand)
				{
					std::cout << "G";
				}
				else if (lhand)
				{
					std::cout << "L";
				}
			}
			else if (mhandfind(row, col))
			{
				std::cout << "M";
			}
			else
			{
				std::cout << " ";
			}
		}
		std::cout << std::endl;
	}
	return;
}

int main()
{
	tu.x = 19;
	tu.y = 12;

	timestruct();
	minutes();
	lhours();
	ghours();

	circle();
	square();

	std::cout << "Local Time: "
		<< yt.hour << ":"
		<< yt.min << "  "
		<< yt.month << "-"
		<< yt.day << "-"
		<< yt.year
		<< "\n";

	std::cout << "Greenwich Mean Time: "
		<< gt.hour << ":"
		<< gt.min << "  "
		<< gt.month << "-"
		<< gt.day << "-"
		<< gt.year
		<< "\n";

	return 0;
}