/*#include <iostream>
#include <string>
#include <vector>
#include <map>

#define astring std::string
#define cvector std::vector

astring rootnote = "";
astring scale = "";
void notation();
int root;
cvector<astring> notes;
cvector<astring> order;
void scaler();


int main()
{
	while (rootnote != "null") {

	std::cout << "Please enter your root note and scale: " << std::endl;
	std::cin >> rootnote >> scale;

	std::cout << "\nroot scale: " << rootnote << " " << scale << std::endl;
	std::cout << std::endl;

		notation();
		scaler();
	}	
	
	return 0;
}

void notation() 
{
	notes.clear();

	cvector<astring> chromatic = { "C", "Db", "D", "Eb", "E", "F", "Gb", "G", "Ab", "A", "Bb", "B" };

	root = std::distance(chromatic.begin(), std::find(chromatic.begin(), chromatic.end(), rootnote));
	
	for (int i = root; i < chromatic.size(); i++) { notes.push_back(chromatic[i]); }
	for (int j = 0; j < root; j++) { notes.push_back(chromatic[j]); }
		
	return;
}

void scaler() {
	order.clear();

	std::map<astring, cvector<int>> scales;
	scales ["Major"] = { 0, 2, 4, 5, 7, 9, 11 };
	scales ["Minor"] = { 0, 2, 3, 5, 7, 8, 10 };
	scales["Melodic"] = { 0, 2, 3, 5, 7, 9, 11 };
	scales ["Harmonic"] = { 0, 2, 3, 5, 7, 8, 11 };
	
	for (auto i : scales[scale])
		order.push_back(notes[i]);
	for (int j = 0; j < order.size(); j++)
		std::cout << order[j] << " ";

	std::cout << "\n\n" << std::endl;

	return;
}
*/

#include <algorithm>
#include <iostream>
#include <iterator>
#include <map>
#include <sstream>
#include <string>
#include <vector>

const std::vector<std::string> chromatic = {
	"C", "Db", "D", "Eb", "E", "F", "Gb", "G", "Ab", "A", "Bb", "B"
};

const std::map<const std::string, const std::vector<int>> degrees = {
	{"Major",       { 0, 2, 4, 5, 7, 9, 11, 12 }},
	{"Minor",       { 0, 2, 3, 5, 7, 8, 10, 12 }},
	{"Harmonic",    { 0, 2, 3, 5, 7, 8, 11, 12 }},
	{"Melodic",     { 0, 2, 3, 5, 7, 9, 11, 12 }}
};

std::string scalenotes(const std::string& rootnote, const std::string& scale) {
	
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