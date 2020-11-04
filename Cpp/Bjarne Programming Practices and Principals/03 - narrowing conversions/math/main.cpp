#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<cmath>

#define string std::string

int main() {
	double d = 0;
	std::cout << "Enter a floating point value or whole number" << std::endl;
		while (std::cin >> d)
		{
			int i = d;
			char c = i;
			int i2 = c;
			std::cout << '\n'
				<< "1. Input Double d == " << d << '\n'
				<< "2. int i = d == " << i << '\n'
				<< "3. char( " << c << " ) = i" << '\n'
				<< "4. int i2 == " << i2 << " = c" << std::endl;
		}
	return 0;
}