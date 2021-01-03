#include "FBullCow.h"
#include <map>

// for Unreal UI
#define TMap std::map
using int32 = int;


FBullCow::FBullCow(){GameStart();} 

int32 FBullCow::GetMaxTries() const
{ 
	TMap<int32, int32> WordLengthtoTries{ {3,4}, {4,6}, {5,8}, {6,10}, {7,12}, };
	return WordLengthtoTries[MyHiddenWord.length()];
}
int32 FBullCow::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCow::GetHiddenWordLength() const { return MyHiddenWord.length(); }
bool FBullCow::WinMatch() const { return bWinMatch; }

FBullCowRatio FBullCow::Score(FString Guess)
{
	MyCurrentTry++;
	FBullCowRatio BullCowRatio;
	int32 WordLength = MyHiddenWord.length(); // assuming same length
	for (int32 WBChar = 0; WBChar < WordLength; WBChar++)
	{
		for (int32 UIChar = 0; UIChar < WordLength; UIChar++)
		{
			if (Guess[UIChar] == MyHiddenWord[WBChar])
			{
				if (UIChar == WBChar) { BullCowRatio.Bull++; }
				else { BullCowRatio.Cow++; }
			}
		}
	}
	if (BullCowRatio.Bull == WordLength) { bWinMatch = true; }
	else { bWinMatch = false; }
	return BullCowRatio;
}

EErrorStat FBullCow::Validate(FString Guess) const
{
	if (!Isogram(Guess))
	{
		return EErrorStat::Not_Isogram;
	}
	else if (Guess.length() != GetHiddenWordLength())
	{
		return EErrorStat::Wrong_Length;
	}
	else if (!Lowercase(Guess))
	{
		return EErrorStat::Invalid_Char;
	}
	else {
		return EErrorStat::Okay;
	}
}
void FBullCow::GameStart()
{
	const FString HiddenWord = "love";
	MyHiddenWord = HiddenWord;
	MyCurrentTry = 1;
	bWinMatch = false;
	return;
}
bool FBullCow::Isogram(FString Word) const
{
	if (Word.length() <= 1) { return true; } // treat 0 and 1 letter string as isogram	
	
	TMap<char, bool> LetterSeen;
	for (auto Letter : Word)
	{
		Letter = tolower(Letter); // loop letters
		if (LetterSeen[Letter]) { return false; } // no isogram
		else { LetterSeen[Letter] = true; } // add letter
	}
	return true; // in cases where /0 is entered
}
bool FBullCow::Lowercase(FString Word) const
{
	for (auto Letter : Word)
	{
		if (!islower(Letter))
		{
			return false;
		}
	}
	return true;
}
