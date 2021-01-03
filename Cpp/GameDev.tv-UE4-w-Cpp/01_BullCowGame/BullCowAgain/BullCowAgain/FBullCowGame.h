#pragma once
#include <string>
#include <vector>

using FString = std::string;
using int32 = int;

struct FBullCowCount
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum class EGuessStatus
{
	Null,
	Ok,
	Not_Isogram,
	Not_Lowercase,
	Wrong_Length
};

class FBullCowGame
{
public:
	FBullCowGame();

	void GameSet();
	void MatchSet();
	void LevelStat();

	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;
	int32 GetCurrentLevel() const;
	bool IsGameWon() const;
	bool IsGameOver() const;
	bool IsMatchWon() const;
	FString ShowWord() const;

	EGuessStatus CheckGuessValidity(FString) const;

	//counts bulls and cows and increases try assuming valid guess
	FBullCowCount SubmitValidGuess(FString);

private:
	int MyCurrentTry;
	int MyMaxTry;
	int MyCurrentLevel;
	const int MyMaxLevel = 7;
	const int MyMinLevel = 3;
	bool bMatchWon;
	bool bLoser;
	bool bGameWon;
	bool bGameOver;
	bool IsIsogram(FString) const;
	bool IsLowercase(FString) const;
	FString MyHiddenWord;
	FString ShowLetters;
};