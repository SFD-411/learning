#include "FBullCowGame.h"
#include <map>
#include <sstream>
#define TMap std::map

FBullCowGame::FBullCowGame() // constructor		
{	GameSet();	}

void FBullCowGame::GameSet() 
{ 
	bGameOver = false;
	MyCurrentLevel = 4;
	
	return; 
}
void FBullCowGame::MatchSet()
{
	MyCurrentTry = 1;

	constexpr int32 MaxTries = 4;
	MyMaxTry = MaxTries;

	const FString HIDDEN_WORD = "hope";
	MyHiddenWord = HIDDEN_WORD;
	ShowLetters = HIDDEN_WORD;

	for (int32 HChar = 0; HChar < MyHiddenWord.length(); HChar++)
	{	ShowLetters[HChar] = '-';	}

	bLoser = false;
	bMatchWon = false;
	return;
}

FString FBullCowGame::ShowWord() const
{
	return ShowLetters;
}

void FBullCowGame::LevelStat()
{
	if (bLoser) { MyCurrentLevel--; }
	if (GetCurrentLevel() < MyMinLevel) { bGameOver = true; }
	if (GetCurrentLevel() > MyMaxLevel) { bGameWon = true; }
	else { bGameWon = false; }
	return;
}

int32 FBullCowGame::GetMaxTries() const { 
	TMap <int32, int32> WordLengthtoMaxTries{ {3,4},{4,5},{5,7},{7,8} };
	return WordLengthtoMaxTries[MyHiddenWord.length()]; }

int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }
int32 FBullCowGame::GetCurrentLevel() const { return MyCurrentLevel; }
bool FBullCowGame::IsMatchWon() const { return bMatchWon; }
bool FBullCowGame::IsGameWon() const { return bGameWon; }
bool FBullCowGame::IsGameOver() const { return bGameOver; }

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	// if not an isogram
	if (!IsIsogram(Guess)) { return EGuessStatus::Not_Isogram; }

	// if not lowercase
	else if (!IsLowercase(Guess)) { return EGuessStatus::Not_Lowercase; }

	// if wrong length
	else if (GetHiddenWordLength() != Guess.length()) { return EGuessStatus::Wrong_Length; }

	else { return EGuessStatus::Ok; }
}

//receives valid guess, increments turncount, returns count
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;
	//setup a return variable
	FBullCowCount BullCowCount;
	int32 HWordLength = MyHiddenWord.length();

	// loop through all letters in hidden word 
	for (int32 HChar = 0; HChar < HWordLength; HChar++) 
	{
		// compare letters against guess 
		for (int32 GChar = 0; GChar < HWordLength; GChar++)
		{
			// if they match
			if (Guess[GChar] == MyHiddenWord[HChar])
			{
				// if they are in the same place
				if (GChar == HChar) 
				{
					BullCowCount.Bulls++; // show bull character
					ShowLetters[HChar] = MyHiddenWord[HChar];
				}
				else 
				{
					BullCowCount.Cows++; // else incriment cows
				}
			}
		}
	}
	if (BullCowCount.Bulls != HWordLength && MyCurrentTry > GetMaxTries()) { bLoser = true; }
	if (BullCowCount.Bulls == HWordLength) { MyCurrentLevel++; bMatchWon = true; }
	else { bMatchWon = false; }
	return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString Word) const
{

	// treat 0 and 1 as isogram
	if (Word.length() <= 1) { return true; }


	TMap<char, bool> FindRepeating;
	// loop through all letters
	for (auto Letter : Word) 
	{
		Letter = tolower(Letter);
			
		if (FindRepeating[Letter]) { return false; }	// we do Not have an isogram
		else { FindRepeating[Letter] = true; } // add letter to map
	
	}
	return true; // in cases where /0 is entered
}

bool FBullCowGame::IsLowercase(FString Word) const
{
	if (Word.length() <= 1) { return true; }
	for (auto Letter : Word) { if (!islower(Letter)) { return false; } }
		return true;
}
