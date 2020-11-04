/*
#include <algorithm>
#include <iostream>
#include <iterator>
#include <map>
#include <sstream>
#include <string>
#include <vector>

const std::vector<std::string> chromatic = {
	"C", "G", "D", "A", "E", "B", "F#", "Db", "Ab", "Eb", "Bb", "F"
};


int root = std::distance(chromatic.begin(), std::find(chromatic.begin(), chromatic.end(), rootnote));
if (root >= chromatic.size()) {
	return "";
}
std::stringstream ss;
for (int i : degrees.at(scale)) {
	ss << chromatic[(root + i) % chromatic.size()] << " ";
}
return ss.str();
}

std::stringstream ask(const std::string& question) {
	std::string line;
	std::cout << question;
	std::getline(std::cin, line);
	return std::stringstream(line);
}

int main()
{
	std::string rootnote, scale;
	while (ask("Please enter your root note and scale: ") >> rootnote >> scale) {
		std::cout << "\nroot scale: " << rootnote << " " << scale
			<< ": " << scalenotes(rootnote, scale) << "\n\n";
	}
}
*/