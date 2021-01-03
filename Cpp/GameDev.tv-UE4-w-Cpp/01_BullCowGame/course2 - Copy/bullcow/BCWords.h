#pragma once
#include <string>

using FString = std::string;

struct Levelset
{
	int32 Level = 4;
};
enum class WordStat
{
	Null,
	Start,
	Next,
	End,
};

class Library
{
public:
	
	Levelset Level(FString);

private:
	void WordCall();
};