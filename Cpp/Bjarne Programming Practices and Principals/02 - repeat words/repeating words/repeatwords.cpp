#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<cmath>

#define string std::string

int main() {
	
	string Previous;
	string Current;
	int wordcount;
	
	std::cout << "Enter sentence to find repeated words: " << std::endl;
	std::cin >> Current;
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
