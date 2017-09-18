/* The game logic (no view code or direct user interaction)
The game is a simple guess the word game based on Mastermind */

#pragma once
#include <string>
#include <cctype>

// to make syntax Unreal friendly
using FString = std::string;
using int32 = int;

struct FBullCowCount 
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum class EGuessStatus
{
	Invalid_Status,
	OK,
	Not_Isogram,
	Wrong_Length,
	Not_Lowercase,
	Non_Alphebetical
};

class FBullCowGame 
{ 
public:
	FBullCowGame(); // constructor

	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;
	bool IsGameWon() const;
	EGuessStatus CheckGuess(FString) const;

	void Reset();
	FBullCowCount SubmitValidGuess(FString);

// see constructor for initialization
private:
	int32 MyCurrentTry;
	FString MyHiddenWord;
	bool bGameIsWon;
	bool IsIsogram(FString) const;
	bool IsLowercase(FString) const;
	bool IsAlpha(FString) const;
};