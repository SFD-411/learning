#include <iostream>
#include <string>
#include "class.h"

void PassByValue(int);
void PassByRef(int &);
void ModifyPerson(Person &inst);


int main()
{
	int num1{ 3 };
	int* pNum = new int;
	*pNum = 5;

	std::cout << "In main(), num1 is " << num1 << " and pNum is " << *pNum << "\n" << std::endl;

	std::cout << "num1 ";
	PassByValue(num1);
	std::cout << "In main(), num1 is " << num1 << "\n" << std::endl;

	std::cout << "\npNum ";
	PassByRef(*pNum);
	std::cout << "In main(), pNum is " << *pNum << "\n" << std::endl;

	std::cout << "\npNum ";
	PassByValue(*pNum);
	std::cout << "In main(), pNum is " << *pNum << "\n" << std::endl;

	double* pDub = new double;
	*pDub = 1972;
	std::cout << "pDub is " << *pDub << "\n" << std::endl;
	delete pDub;

	Person inst( "Charles", 23, 57, 180 );

	std::cout << inst.getName() << " is " << inst.getAge() << ".\n"
		<< "He is " << inst.getHeight() << " inches and " << inst.getWeight() 
		<< " pounds.\n" << std::endl;

	std::cout << inst.getName() << " changed his name to ";
	ModifyPerson(inst);
	std::cout << inst.getName() << std::endl;

	return 0;
}

void PassByValue(int num)
{
	std::cout << "In PassByValue()\n";
	num++;
	std::cout << "num is now " << num << "\n" << std::endl;

	return;
}

void PassByRef(int &ref)
{
	std::cout << "In PassByRef()\n";
	ref = 50;
	std::cout << "pNum is now " << ref << "\n" << std::endl;

	return;
}

void ModifyPerson(Person &inst) 
{
	inst.setName("Janette");

	return;
}
