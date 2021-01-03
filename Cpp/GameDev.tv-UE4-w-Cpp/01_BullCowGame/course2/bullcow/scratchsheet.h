

// develop level changing infrastructure
struct LevelCap
{
	int32 MinLevel = 3;
	int32 MaxLevel = 7;
};
// define current level and next level
enum class ELevelStat
{
	Start,
	Next_Level,
	Last_Level,
	Current_Level,
	Final,
	Game_Over,
};

////////////////////////////
// TODO Heigharchy
// TODO findlevel = FindWord based on previous level +/- 
ELevelStat NewLevel(FString FindWord); // define new level
ELevelStat Library(FString FindWord); // Find Words and Output to HiddenWord
void ThreeStrikes() const; // counts attempts : 3x cap -1 per hints : 1 redo on new level or game over
int32 NewLevel() const; // receive current level finding word length
bool bWinGame() const; // current level > final level
};



// TODO Build Heirarchy
// find level mechanism
ELevelStat FindLevel(FString FindWord) {
	// if firstlevel <= currentlevel
	// for not wingame
	// if maxredo
	// lose level and -1 FindWord
	// else if winmatch
	// gain level and +1 FindWord
	// else game over
	return ELevelStat::Game_Over;
}
// reset level, find next level, count redos
void LevelSystem(FString FindWord)
{	// start level at 3 in reset - do when
	// input next level	through FindWord Value out to maxtry
	// count maxredo and factor redo count per hints and losses
	return;
}
// store and find words based on level size
ELevelStat Library(FString FindWord)
{	// input from FindWord Length
	// choose word by wordlength
	// attach hint and definition and route to output to main
	return ELevelStat::Next_Level;
}
// generate new word length
int32 FBullCow::NewLevel() const
{	//do 
	// return nextlevel variable
	// when next level < final level
	return 0;
}
// win game when match = greater than last level
bool FBullCow::bWinGame() const
{	// when nextlevel > finallevel
	// send wingame
	// else run FindLevel
	return false;
}

