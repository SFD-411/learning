#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<cmath>
inline void keep_window_open() { char ch; std::cin >> ch; }

#define phrase std::string

int main() {
	double n;

	do  {
		std::cout << "Please enter a floating-point value: " << std::endl;
		std::cin >> n;
		std::cout << "\n n == " << n << std::endl 
			<< "\n n+1 == " << n + 1
			<< "\n three * n == " << 3 * n
			<< "\n twice n == " << n + n
			<< "\n n2 == " << n * n
			<< "\n half of n == " << n / 2
			<< "\n root of n == " << sqrt(n) << "\n\n" ;
	} while (n != 111.111);

	return 0;
}