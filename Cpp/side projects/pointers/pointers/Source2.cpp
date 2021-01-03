#include <algorithm>
#include <iostream>
#include <string>

double zed();
double complex(double a, double b);

struct imaginary{
	double sol;
	double x;
};

double i()
{
	imaginary v;
	v.sol = -1;
	v.x;
	return v.x = sqrt(v.sol);
}

int main()
{
	double var, exp;
	std::cout << "enter two numbers: " << std::endl;
	std::cin >> var;
	std::cout << ", ";
	std::cin >> exp;
	std::cout << "\n" << complex(var, exp) << std::endl;



	return 0;
}


double complex(double a, double b) 
{
	return a + (b * i());
}
