#include <iostream>
#include <string>
#include <stdlib.h>

#define string std::string

string uname_first;
string uname_last;
string aname_first;
string fname;
constexpr int size{ 6 };
char fsex[size];
void friendsex();
int aage;

int main() {

	std::cout << "What is your first and last name?" << std::endl;
	std::cin >> uname_first >> uname_last;
	
	std::cout << "\nHello, " << uname_first << std::endl;
	
	std::cout << "\nWhat is the first name of the person you are writing ? " << std::endl;
	std::cin >> aname_first;
	
	std::cout << "\nWhat is the first name of one of your friends?" << std::endl;
	std::cin >> fname;

	friendsex();

	std::cout << "\nHow old is " << aname_first << "?" << std::endl;
	std::cin >> aage;
	
	bool bage = false;

	while (!bage) {
		if (aage <= 0 || aage >= 110)
		{
			std::cout << "\nYou are kidding.. " << aname_first << " can't be " << aage << "... try again." << std::endl;
			std::cout << "\nHow old is " << aname_first << "?" << std::endl;
			std::cin >> aage;
		}

		else if (aage > 0 && aage < 17)
		{
			bage = true;
			std::cout << "\nSo.. " << aname_first << " is turning " << aage + 1 << " soon!" << std::endl;
		}

		else if (aage == 17)
		{
			bage = true;
			std::cout << "\nNext year " << aname_first << " will be able to vote." << std::endl;
				}

		else if (aage > 70 && aage < 110)
		{
			bage = true;
			std::cout << "I hope " << aname_first << " is enjoying retirement at the ripe age of " << aage << std::endl;
		}

		else if (aage < 70 && aage > 19)
		{
			bage = true;
			std::cout << "\nSo.. " << aname_first << " is turning " << aage + 1 << " soon!" << std::endl;
		}

		else
		{
			std::cout << "please enter a whole number." << std::endl;
			std::cout << "\nHow old is " << aname_first << "?" << std::endl;
			std::cin >> aage;
		}
	}

	std::cout << "\nThank you for your time! Have a good day " << uname_first << " " << uname_last << std::endl;
	return 0;
}

void friendsex() 
{
	std::cout << "\nIs " << fname << " a Male or Female?" << std::endl;
	std::cin >> fsex;

	if (fsex[0] == 'm' || fsex[0] == 'M')
		std::cout << "\nIf you see " << fname << ", tell him I said Hello!" << std::endl;
	else if (fsex[0] == 'f' || fsex[0] == 'F')
		std::cout << "\nIf you see " << fname << ", tell her I said Hello!" << std::endl;
	else
		std::cout << "invalid gender" << std::endl;
	return;
}