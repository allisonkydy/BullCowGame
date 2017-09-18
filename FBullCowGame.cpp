#pragma once
#include "FBullCowGame.h"
#include <map>

// to make syntax Unreal friendly
#define TMap std::map
using int32 = int;

FBullCowGame::FBullCowGame() { Reset(); } // define constructor

int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }
bool FBullCowGame::IsGameWon() const { return bGameIsWon; }

int32 FBullCowGame::GetMaxTries() const 
{ 
	TMap<int32, int32> WordLengthToMaxTries{ {3,8}, {4,10}, {5,13}, {6,18}, {7,25} };
	return WordLengthToMaxTries[MyHiddenWord.length()];
}

void FBullCowGame::Reset()
{
	const FString HIDDEN_WORD = "bong"; // this MUST be an isogram

	MyHiddenWord = HIDDEN_WORD;
	MyCurrentTry = 1;
	bGameIsWon = false;

	return;
}

//receives a VALID guess, increments turn and returns count
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{		
	MyCurrentTry++;
	FBullCowCount BullCowCount;
	int32 WordLength = MyHiddenWord.length(); // assuming same length as guess

	// loop through all letters in the  hidden word
	for (int32 MHWChar = 0; MHWChar < WordLength; MHWChar++) {
		// compare letters against the guess
		for (int32 GChar = 0; GChar < WordLength; GChar++) {
			// if they match then...
			if (Guess[GChar] == MyHiddenWord[MHWChar]) {
				// if they're in the same place
				if (MHWChar == GChar) {
					BullCowCount.Bulls++;
				}
				else {
					BullCowCount.Cows++;
				}
			}
		}
	}
	if (BullCowCount.Bulls == WordLength)
	{
		bGameIsWon = true;
	}
	else 
	{
		bGameIsWon = false;
	}
	return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString Word) const
{
	// treat 0 or 1 letter words as isograms
	if (Word.length() <= 1) { return true; }

	TMap<char, bool> LetterSeen; // setup our map
	for (auto Letter : Word)	 // for all letters of the word
	{
		Letter = tolower(Letter); // handle mixed case

		if (LetterSeen[Letter]) 	// if the letter is in the map
		{ 
			return false;			// we do NOT have an isogram
		}
		else
		{
			LetterSeen[Letter] = true;	// add the letter to the map as seen
		}
	}
	return true; // for example, in cases when /0 is entered
}

bool FBullCowGame::IsLowercase(FString Word) const
{
	for (auto Letter : Word) // for all letters of the word
	{
		if (!isalpha(Letter)) // if the Letter is not alphabetical, it is lowercase
		{
			return true;
		}
		else if (!islower(Letter))	// if the letter is NOT lowercase
		{
			return false;
		}
	}
	return true;
}

bool FBullCowGame::IsAlpha(FString Word) const
{
	for (auto Letter : Word)
	{
		if (!isalpha(Letter))
		{
			return false;
		}
	}
	return true;
}

EGuessStatus FBullCowGame::CheckGuess(FString Guess) const
{
	if (! IsIsogram(Guess)) // if the guess isn't an isogram
	{
		return EGuessStatus::Not_Isogram;
	}
	else if (! IsLowercase(Guess))	// if the guess isn't all lowercase 
	{
		return EGuessStatus::Not_Lowercase; 
	}
	else if (GetHiddenWordLength() != Guess.length())	// if the guess length is wrong
	{
		return EGuessStatus::Wrong_Length;
	}
	else if (! IsAlpha(Guess))	// if the guess contains non-alpha characters
	{
		return EGuessStatus::Non_Alphebetical; 
	}
	else
	{
		return EGuessStatus::OK;
	}
}
