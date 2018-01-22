/* This is the console executable that basically acts as the view, is responsible for user interaction
*/

#include <iostream>
#include <string>
#include "FBullCowGame.h"

using FText = std::string;
using int32 = int;

void PrintIntro();
std::string GetValidGuess();
void PlayGame();
bool AskToPlayAgain();

FBullCowGame BCGame;

int main()
{
	do
	{
		PrintIntro();
		PlayGame();
		//TODO add game summary
	} 
	while (AskToPlayAgain());

	std::cout << std::endl;
	return 0;
}

void PrintIntro()
{
	std::cout << "Welcome to Bulls and Cows, a sort of fun word game" << std::endl;
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength() << " letter isogram?" << std::endl;
	return;
}

FText GetValidGuess()
{
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	do
	{
		std::cout << "Try " << BCGame.GetCurrentTry() << ". Enter your guess" << std::endl;

		FText Guess;
		std::getline(std::cin, Guess);

		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status)
		{
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word" << std::endl << std::endl;
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter an isogram" << std::endl << std::endl;
			break;
		case EGuessStatus::Non_Alpha_Characters:
			std::cout << "Please enter a word that's only letters" << std::endl << std::endl;
			break;
		default:
			return Guess;
		}
	} while (Status != EGuessStatus::OK);
}

void PlayGame()
{
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();
	//TODO refactor to while loop
	for (int32 i = 0; i < MaxTries; i++)
	{
		FText Guess = GetValidGuess();
		
		//Submit valid guess to game		
		FBullCowCount BullCowCount = BCGame.SubmitGuess(Guess);
		std::cout << "Bulls: " << BullCowCount.Bulls << "     Cows: " << BullCowCount.Cows << std::endl;
	}
}

bool AskToPlayAgain()
{
	std::cout << "Do you want to play again?" << std::endl;
	FText Response;
	std::getline(std::cin, Response);
	
	return tolower(Response[0]) == 'y';
}

