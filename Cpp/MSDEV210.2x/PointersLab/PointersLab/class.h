#pragma once


class Person
{
public:
	Person() {}
	Person(std::string newname, int newAge, int newHeight, int newWeight)
	{
		name = newname;
		age = newAge;
		height = newHeight;
		weight = newWeight;
	}

	void setName(std::string newname) { name = newname; return; }
	void setAge(int newage) { age = newage; return; }
	void setHeight(int newheight) { height = newheight; return; }
	void setWeight(int newweight) { weight = newweight; return; }

	std::string getName() const { return name; }
	int getAge() const { return age; }
	int getHeight() const { return height; }
	int getWeight() const { return weight; }

private:
	std::string name;
	int age, height, weight;
};
