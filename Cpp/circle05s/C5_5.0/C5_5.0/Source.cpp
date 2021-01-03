#include <iostream>
#include "Note_Directory.h"


void ass(const std::vector<std::string> &pos, const std::vector<intervals> &Major);

struct notestat
{
	int position;
	std::string incriment;
	std::string key[P8];
	std::string alt_key[P8];
	std::vector<std::string> harmonies[M2];
}sNote[(P8 + P4)]; 

int main()
{
	const std::vector<std::string> pos { "P1", "m2", "M2", "m3", "M3", "P4", "TT", "P5", "m6", "M6", "m7", "M7", "P8" };
	const std::vector<intervals> Major = { P1, M2, M3, P4, P5, M6, M7, P8 };
	std::vector<intervals> harmony{ P1,M2,M3 };
	

	ass(pos, Major);

	std::cout << "\n\n" << "\tCircle of Fifths Struct" << "\n"
		<< "index " << "\tkey" << "\tpos" << "\tincr" << "\tscale" << "\tharmonies" << std::endl;

	bool altern = false;
	for (int i = P1; i < P8; i++)
	{
		if (i > m3 && i < M6) { altern = true; }
		else altern = false;

		for (auto h : harmony)
			sNote[i].harmonies[P1].push_back(sNote[i].key[h]);

		std::cout << " " << i << "\t" 
			<< sNote[i].key[P1] << "\t"
			<< sNote[i].position << "\t"
			<< sNote[i].incriment << "\t";
		for (int j = P1; j < P8; j++)
		{	std::cout << sNote[i].key[j] << " ";	}
		for (int k = P1; k < m3; k++)
		{	std::cout << sNote[i].harmonies[P1][k] << " ";	}
		std::cout << std::endl;
		
		if (altern)
		{
			for (auto n : harmony)
				sNote[i].harmonies[m2].push_back(sNote[i].alt_key[n]);
			std::cout << " " << i << "\t"
				<< sNote[i].alt_key[P1] << "\t"
				<< sNote[i].position << "\t"
				<< sNote[i].incriment << "\t";
			for (int l = P1; l < P8; l++)
			{	std::cout << sNote[i].alt_key[l] << " ";	}
			for (int m = P1; m < m3; m++)
			{
				std::cout << sNote[i].harmonies[m2][m] << " ";
			}
			std::cout << std::endl;
		}
	}



	return 0;

}


void ass(const std::vector<std::string> &pos, const std::vector<intervals> &Major) {
	int _5th = P1;
	int step = P1;
	do
	{
		int place = P1;
		int add = P1;
		if (step < M3)
		{
			sNote[step].position = _5th;
			sNote[step].incriment = pos[_5th];
			for (auto i : Major)
			{
				add = _5th + i;
				sNote[step].key[place] = (sharps[(add % P8)]);
				place++;
			}
		}
		else if (step > m3 && step < TT)
		{
			sNote[step].position = _5th;
			sNote[step].incriment = pos[_5th];
			for (auto i : Major)
			{
				add = _5th + i;
				sNote[step].key[place] = (sharps[(add % P8)]);
				sNote[step].alt_key[place] = (flats_double[(add % P8)]);
				place++;
			}
		}
		else if (step == TT)
		{

			sNote[step].position = _5th;
			sNote[step].incriment = pos[_5th];

			for (auto i : Major)
			{

				add = _5th + i;
				sNote[step].key[place] = (sharps_double[(add % P8)]);
				sNote[step].alt_key[place] = (flats_double[(add % P8)]);
				place++;
			}
		}
		else if (step > TT && step < M6)
		{
			sNote[step].position = _5th;
			sNote[step].incriment = pos[_5th];

			for (auto i : Major)
			{
				add = _5th + i;
				sNote[step].key[place] = (flats[(add % P8)]);
				sNote[step].alt_key[place] = (sharps_double[(add % P8)]);
				place++;
			}
		}
		else if (step > m6)
		{
			sNote[step].position = _5th;
			sNote[step].incriment = pos[_5th];
			for (auto i : Major)
			{
				add = _5th + i;
				sNote[step].key[place] = (flats[(add % P8)]);
				place++;
			}
		}

		_5th = (_5th + P5) % P8;
		step++;
	} while (_5th != P1);
}

class scaler
{
public:
	enum class eRing
	{
		blank,
		inner,
		middle,
		outter
	};
	struct scales
	{
		std::string inner = "";
		std::string middle = "";
		std::string outter = "";
	} scale;

	std::map < eRing, std::string > places = { {eRing::inner, scale.inner}, { eRing::middle, scale.middle }, {eRing::outter, scale.outter } };
};