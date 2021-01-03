#include <iostream>
#include <string>
#include "FBullCowGame.h"

using FText = std::string;
using int32 = int;

FBullCowGame BCG;

void GameLogic();
void PrintIntro();
void PrintGameSummary();

FText GetValidGuess();
bool TryAgain();
bool NewGame();

int main() 
{
	bool bRetry = false;
	bool bNewGame = false;
	BCG.MatchSet();

	
	constexpr int32 redo = 1;  // everybody gets one
	do 
	{
		BCG.GameSet(); // initializes game
		PrintIntro();  
		int32 doOver = 0;
		do
		{
			BCG.MatchSet(); // updates match details
			do
			{
				GameLogic(); // sets game conditions, runs game loop, and updates game conditions
				
				if (doOver != redo && !BCG.IsMatchWon() && !BCG.IsGameWon())
				{	doOver++; bRetry = TryAgain();	}
				else if (BCG.IsMatchWon()) { doOver = 0; }
				else (bRetry = false);
			} 
			while (bRetry);
			PrintGameSummary();
		} 
		while (!BCG.IsGameWon() && bRetry || BCG.IsMatchWon() && !BCG.IsGameWon());
		bNewGame = NewGame();
	} 
	while (bNewGame);

	return 0;
}

void GameLogic()
{
	
	int32 MaxTries = BCG.GetMaxTries();
	BCG.MatchSet();
	while (!BCG.IsMatchWon() && !BCG.IsGameWon() && BCG.GetCurrentTry() <= MaxTries) 
	{
			FText Guess = GetValidGuess();

			//send valid guess to the game  and get count
			FBullCowCount BullCowCount = BCG.SubmitValidGuess(Guess);

			
			std::cout << "Bulls = " << BullCowCount.Bulls << "\t"
						<< "Cows = " << BullCowCount.Cows << std::endl;
			std::cout << "Hidden Word : " << BCG.ShowWord() << "\n" << std::endl;
			std::cout << std::endl;
	}
	BCG.LevelStat();

	return;
}

void PrintIntro() 
{
	const int32 WORD_LENGTH = BCG.GetHiddenWordLength();
	std::cout << "\nWelcome to Bulls and Cows\n"
		<< "Guess the " << WORD_LENGTH << " Letter Word in " << BCG.GetMaxTries() << " tries or less!\n\n" << std::endl;
	return;
}

void PrintGameSummary()
{
	if (BCG.IsGameWon()) {
		std::cout << "\nYOU ARE A WINNER!!\n" << std::endl;
	}
	else if (BCG.IsMatchWon() && !BCG.IsGameWon()) {
		std::cout << "\nGood Job! Next Level!\n" << std::endl;
	}
	else if (!BCG.IsGameWon() && !BCG.IsMatchWon()) {
		std::cout << "You Lost!! Please Try Again!!\n" << std::endl;
	}
}

FText GetValidGuess()
{
	FText Guess = "";
	EGuessStatus Status = EGuessStatus::Null;

	do{
		int32 CurrentTry = BCG.GetCurrentTry();
		
	std::cout << "Level " << BCG.GetCurrentLevel() << "  " << "Turn #" << CurrentTry 
			<< " of " << BCG.GetMaxTries() << ". \nPlease enter a guess: ";
	
	std::getline(std::cin, Guess);


	Status = BCG.CheckGuessValidity(Guess);
	switch (Status)
	{
	case EGuessStatus::Wrong_Length:
		std::cout << "\nPlease enter a " << BCG.GetHiddenWordLength() << " letter word. \n";
		break;
	case EGuessStatus::Not_Isogram:
		std::cout << "\nAn Isogram is a Word with No Repeating Letters. Please try again! \n";
		break;
	case EGuessStatus::Not_Lowercase:
		std::cout << "\nPlease use lowercase letters.\n";
		break;
	default:
		// assume valid guess
		break;
	}
	std::cout << std::endl;
	} while (Status != EGuessStatus::Ok);
	return Guess;
}

bool TryAgain()
{
	std::cout << "You Lose!\n" << "\nWould you like to try again? \nYes or No? ";
	FText Retry = "";
	std::getline(std::cin, Retry);
	std::cout << std::endl;
	return (Retry[0] == 'y') || (Retry[0] == 'Y');
}

bool NewGame()
{
	std::cout << "\n Would you like to play again? \nYes or No? ";
	FText Replay = "";
	std::getline(std::cin, Replay);
	std::cout << std::endl;
	return (Replay[0] == 'y') || (Replay[0] == 'Y');
}
