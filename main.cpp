/* This is the console executable that makes use of the BullCow class.
This acts as the view in a  MVC pattern, and is responsible for all user interaction. 
For game logic, see FBullCowGame class.	
*/

#pragma once
#include <iostream>
#include <string>
#include "FBullCowGame.h"

// to make syntax Unreal friendly
using FText = std::string;
using int32 = int;

void PrintIntro();
void PlayGame();
FText GetValidGuess();
bool AskToPlayAgain();
void PrintGameSummary();

FBullCowGame BCGame; // instantiate a new game, which we reuse across plays

// entry point for the application
int main()
{
	bool bPlayAgain = false;
	do {
		PrintIntro();
		PlayGame();
		bPlayAgain = AskToPlayAgain();
	} while (bPlayAgain);

	std::cout << std::endl;
	return 0; // exit the application
}


void PrintIntro()
{
	int32 HWLength = BCGame.GetHiddenWordLength();
	int32 MaxTries = BCGame.GetMaxTries();

	std::cout << "Welcome to Bulls and Cows, a shitty word game!" << std::endl;
	std::cout << "Can you guess the " << HWLength << " letter isogram I'm thinking of?\n\n";
	std::cout << "A Bull is a right letter in the right place.\n";
	std::cout << "A Cow is a right letter in the wrong place.\n\n";
	std::cout << "You have " << MaxTries << " tries." << std::endl;
	std::cout << std::endl;
	return;
}

// plays a single game to completion
void PlayGame()
{
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries(); 

	// loop asking for guesses while game is NOT won and there are still tries remaining
	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries)
	{
		FText Guess = GetValidGuess(); 

		// submit guess and increment counts and turn #
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);

		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << " Cows = " << BullCowCount.Cows << "\n\n";
	}
	PrintGameSummary();
	return;
}


// loop continuously until user inputs a valid guess
FText GetValidGuess()
{
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	FText Guess = "";

	do {
		// get a guess from the player
		int32 CurrentTry = BCGame.GetCurrentTry();
		std::cout << "Try #" << CurrentTry << ". ";
		std::cout << "Enter your guess: ";
		std::getline(std::cin, Guess);

		// check status and give error feedback
		Status = BCGame.CheckGuess(Guess);
		switch (Status)
		{
		case EGuessStatus::Wrong_Length:
			std::cout << "Enter a " << BCGame.GetHiddenWordLength() << " letter word ya dingus.\n\n";
			break;
		case EGuessStatus::Non_Alphebetical:
			std::cout << "Letters only stupid.\n\n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Letters gotta be different, son.\n\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Think ur a BIG BOI huh?? lowercase only biiiitch.\n\n";
			break;
		default:  // assume the guess is valid
			break;
		} 	
	} while (Status != EGuessStatus::OK); // keep looping until we get no errors			
	return Guess;
}

// check if player wants to play again
bool AskToPlayAgain()
{	
	std::cout << "Do you want to play again with the same hidden word? (y/n) ";
    FText Response = "";
	std::getline(std::cin, Response);
	std::cout << std::endl;

	return (Response[0] == 'y') || (Response[0] == 'Y');
}

// summarize the game
void PrintGameSummary()
{
	if (BCGame.IsGameWon())
	{
		std::cout << "YOU WON - GOOD JOB\n";
	}
	else
	{
		std::cout << "SORRY YOU LOST\n";
	}

	return;
}
