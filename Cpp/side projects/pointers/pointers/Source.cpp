#include <iostream>
#include <string>

int main() 
{
	std::string test = "Hello Lainey";

	std::string* ptr = &test;
	std::cout << ptr << " is " << *ptr << std::endl;
	
	return 0;

}