#include <algorithm> 
#include <iostream>
#include <iterator>
#include <string>
#include <sstream>
#include <vector> 
#include <map>

const std::vector<std::string> st_sharps{ "C","C#","D","D#","E","F","F#","G","G#","A","A#","B" };
const std::vector<std::string> st_flats{ "C","Db","D","Eb","E","F","Gb","G","Ab","A","Bb","B" };

int maj_step = 0;
int min_step = 0;
constexpr int H = 1;
constexpr int W = 2;
constexpr int Tre = 3;
constexpr int Fif = 5;
constexpr int Sev = 7;
const int size = st_flats.size();
const std::vector<int> Major = { W, W, H, W, W, W, H };

std::stringstream maj_scale;
std::stringstream min_scale;
std::stringstream sfives;
std::stringstream bfives;
std::stringstream relmin_fives;
std::stringstream dim_fives;

std::stringstream ask(const std::string& question) {
	std::string line;
	std::cout << question;
	std::getline(std::cin, line);
	return std::stringstream(line);
}

int main()
{
	std::string rootnote;
	std::cout << "Please enter your root note and scale: " << std::endl;
	std::cin >> rootnote;

		int root = std::distance(st_sharps.begin(), std::find(st_sharps.begin(), st_sharps.end(), rootnote));

		//Circle of Fifths
			// sharps
		for (int j = 0; j < size; j++) {

			int step = j * Sev;
			sfives << st_sharps[(root + step) % size] << " ";
			bfives << st_flats[(root + step) % size] << " ";
			relmin_fives << st_sharps[((size - Tre) + (root + step)) % size] << " ";
			dim_fives << st_sharps[((size - H) + (root + step)) % size] << " ";
		}

		std::cout << "Circle of Fifths:\n";

		std::cout << "Major >> Relative Minor >> Diminished " << std::endl;
		std::cout << "Maj: " << sfives.str() << std::endl;
		std::cout << "Min: " << relmin_fives.str() << std::endl;
		std::cout << "Dim: " << dim_fives.str() << std::endl;
		std::cout << "\nflats: " << bfives.str() << "\n" << std::endl;

		int minor = size - Tre;

		//Major and Minor Scales
		for (int i = 0; i < Major.size(); i++) {
			maj_scale << st_sharps[(root + maj_step) % size] << " ";
			min_scale << st_flats[(root + minor + min_step) % size] << " ";
			min_step += Major[(i + Fif) % Major.size()];
			maj_step += Major[(i) % Major.size()];
		}
		std::cout << "C Major:\n" << maj_scale.str() << "\n" << std::endl;
		std::cout << "A Minor:\n" << min_scale.str() << "\n" << std::endl;
	return 0;
}