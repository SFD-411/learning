#pragma once
#pragma once

class FBullCow
{
public:
	void WinMatch();
	void LoseMatch();
	void LoseGame(); // focus
	int GetCurrentTry(); // focus
	int GetMaxTry();
	int GetDiffLVL();
	string GetGoodGuess();
	string GetBadGuess();
	string GetHelp();
	bool WinGame(); // focus
	bool

		//implementation details 
private:
	int MyCurrentTry();
	int MyMaxTries();
	int GameOver();
	int Winner();
	string LevelSystem();
	string MagicNumbers();
	void WordLibrary();
};

void PrintIntro();
void LoopCommand();
string GetGuess();
bool PlayAgain();