/* Console Executable using BC Class
Acts as view in MVC pattern responsible for UI.
For Game Logic see FBullCowGame class.*/

#pragma once
#include <iostream>
#include <string>
#include "FBullCow.h"
#include "BCWords.h"

// for Unreal UI
using FText = std::string;
using int32 = int;

// function prototype outside calss
void PrintMain();
void GameCommand();
void WinLoseStat();
FText ValidateGuess();
bool PlayAgain();


FBullCow BCGame; // instantiate new game to completion


int main()
{
	PrintMain();
	bool bPlayAgain = false;
	do
	{
		GameCommand();
		bPlayAgain = PlayAgain();
		std::cout << std::endl << std::endl;
	} while (bPlayAgain);
	return 0;
}

void PrintMain()
{
	std::cout << "\n\n		Hey Zach!\n\n";
	std::cout << "   Welcome to the Word Game!\n\n" << std::endl;
	std::cout << "   Rules: " << std::endl;
	std::cout << "     - Guess the Hidden Word." << std::endl;
	std::cout << "     - Type 'HINT' if you need a clue." << std::endl;
	std::cout << "     - Your # of Tries is based on the difficulty of the Word." << std::endl;
	std::cout << "     - Guessing the Correct Letter in the Correct Place will display a Bull" << std::endl;
	std::cout << "     - Guessing the Correct Letter in the Incorrect Place will display a Cow" << std::endl;
	std::cout << "\n\n		 GOOD LUCK!!\n" << std::endl;
	std::cout << std::endl;
	return;
}

// TODO set up function to pull from library
void GameCommand()
{
	BCGame.DefineGame();  // zero state
	int32 MaxTry = BCGame.GetMaxTries();  // word conditions
	
	std::cout << "  -- YOU HAVE " << MaxTry << " TRIES TO GUESS THE ISOGRAM --\n";
	std::cout << "  --  TIP:  NO LETTERS WILL BE USED TWICE  --\n";
	std::cout << std::endl << std::endl;
	
	// incorporate game vs. match distinction 
	while(!BCGame.WinMatch() && BCGame.GetCurrentTry() <= MaxTry)
	{
		FText Guess = ValidateGuess();
		FBullCowRatio BullCowRatio = BCGame.Score(Guess);
		std::cout << " \n  ------------------------------------\n" << std::endl;
		std::cout << " - YOU HAVE FOUND " << BullCowRatio.Bull;
		std::cout << " Bulls AND " << BullCowRatio.Cow << " Cows! - " << std::endl;
		std::cout << " \n  ------------------------------------\n" << std::endl;
	}
		
	WinLoseStat();
	return;
}
FText ValidateGuess()
{
	FText Guess = "";
	EErrorStat Status = EErrorStat::NoStat;
	
	do
	{
		{
			int32 MyCurrentTry = BCGame.GetCurrentTry();
			std::cout << "  - Turn # " << MyCurrentTry << " of " << BCGame.GetMaxTries() << std::endl;
			std::cout << " Can You Guess the " << BCGame.GetHiddenWordLength() << " letter isogram? \n\n		";
			std::getline(std::cin, Guess);
			
			Status = BCGame.Validate(Guess);
			switch (Status)
			{
			case EErrorStat::Wrong_Length:
				std::cout << " \n  ------------------------------------\n" << std::endl;
				std::cout << " Please enter a " << BCGame.GetHiddenWordLength() << " letter word? K. Thnx! :D ";
				std::cout << " \n\n  ------------------------------------\n\n" << std::endl;
				break;
			case EErrorStat::Invalid_Char:
				std::cout << " \n  ------------------------------------\n" << std::endl;
				std::cout << " no capital letters or crazy symbols okay?";
				std::cout << " \n\n  ------------------------------------\n\n" << std::endl;
				break;
			case EErrorStat::Not_Isogram:
				std::cout << " \n  ------------------------------------\n" << std::endl;
				std::cout << " Wrong Answer Buddy.. \n";
				std::cout << "   An Isogram is a word that only uses each\n letter one time.	\n			 Please Try Again. ";
				std::cout << " \n\n  ------------------------------------\n\n" << std::endl;
				break;
			default:
				break;
			}
		}
	} while (Status != EErrorStat::Okay);
	
	return Guess;
}
bool PlayAgain()
{
	std::cout << "\nWould You Like To Try The Same Word Again?! \n\n	    :D  ?Y/N?  :D \n\n		";
	FText Response = "";
	std::getline(std::cin, Response);
	return (Response[0] == 'y') || (Response[0] == 'Y');
	return false;
}
// TODO incorporate level system
void WinLoseStat() {
	if (BCGame.WinMatch())
	{
		std::cout << "	   ------------------" << std::endl;
		std::cout << "	   ------------------\n" << std::endl;
		std::cout << "	  GOOD JOB!!  YOU WIN!!\n" << std::endl;
		std::cout << "	   ------------------" << std::endl;
		std::cout << " 	   ------------------\n" << std::endl;
	}
	else 
	{
		std::cout << "	   ------------------" << std::endl;
		std::cout << "	   ------------------\n" << std::endl;
		std::cout << "	 YOU LOSE!! TRY AGAIN!!\n" << std::endl;
		std::cout << "	   ------------------" << std::endl;
		std::cout << " 	   ------------------\n" << std::endl;
	}
}

