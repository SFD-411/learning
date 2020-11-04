/* game logic with no view code or UI */
// #pragma once
#include <std>
#include <string>

 // for Unreal UI
using FString = std::string; 
using int32 = int;

struct FBullCowRatio {
	int32 Bull = 0;
	int32 Cow = 0;
};
enum class EErrorStat
{
	NoStat,
	Okay,
	Not_Isogram,
	Invalid_Char,
	Wrong_Length,
};
class FBullCow
{
public:
	FBullCow(); // constructor
	
	int32 GetMaxTries() const;             // via tmap per wordlength
	int32 GetCurrentTry() const;           // plus 1 via BCRatio
	int32 GetHiddenWordLength() const;     // input hidden word length
	EErrorStat Validate(FString) const;     // erorr pulls string per boolwinconst
	bool WinMatch() const;                 // input bool status per score
	void GameStart();                     // initial values
	FBullCowRatio Score(FString);          // turncounter and score

	
private: //implementation details
	int32 MyCurrentTry;
	int32 MyMaxTry;
	FString MyHiddenWord;                  // via GameStart hidden word creates variable
	bool Isogram(FString) const;
	bool Lowercase(FString) const;
	bool bWinMatch;                        // pulls true if BCRatio is Wordlength
};

