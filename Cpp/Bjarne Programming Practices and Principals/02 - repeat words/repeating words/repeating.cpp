#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<cmath>

#define string std::string

int main() {

	string Previous;
	string Current;
	int wordcount = 0;

	std::cout << "Enter sentence to find repeated words: " << std::endl;
	std::cin;
	while (std::cin >> Current)
	{
		++wordcount;
		if (Previous == Current)
		{
			std::cout << "repeated word # " << wordcount << ": " << Current << '\n';
		}
		Previous = Current;
	}

	return 0;
}
