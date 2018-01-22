#include "FBullCowGame.h"

FBullCowGame::FBullCowGame()
{
	Reset();
}

void FBullCowGame::Reset()
{
	constexpr int32 MAX_TRIES = 8;
	const FString HIDDEN_WORD = "ant";
	MyMaxTries = MAX_TRIES;

	MyCurrentTry = 1;	
	MyHiddenWord = HIDDEN_WORD;
	return;
}

int32 FBullCowGame::GetMaxTries() const
{
	return MyMaxTries;
}

int32 FBullCowGame::GetCurrentTry() const
{
	return MyCurrentTry;
}

int32 FBullCowGame::GetHiddenWordLength() const
{
	return MyHiddenWord.length();
}

bool FBullCowGame::IsGameWon() const
{
	return false;
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	//if guess length is wrong, return error
	if (Guess.length() != GetHiddenWordLength())
	{
		return EGuessStatus::Wrong_Length;
	}

	//if guess is not an isogram, return error
	for (int32 i = 0; i < Guess.length(); i++)
	{
		for (int32 j = i + 1; j < Guess.length(); j++)
		{
			if (tolower(Guess[i]) == tolower(Guess[j]))
			{
				return EGuessStatus::Not_Isogram;
			}
		}
	}

	//if guess has non alpha character, return error
	for (int32 i = 0; i < Guess.length(); i++)
	{
		if (!isalpha(Guess[i]))
		{
			return EGuessStatus::Non_Alpha_Characters;
		}
	}

	//otherwise return ok
	return EGuessStatus::OK;
}

//receives a valid guess, increments turn, returns count
FBullCowCount FBullCowGame::SubmitGuess(FString Guess)
{
	//increment turn count
	MyCurrentTry++;

	//setup return variable
	FBullCowCount BullCowCount;

	//loop through all letters in guess
	int32 HiddenWordLength = MyHiddenWord.length();
	for (int32 i = 0; i < HiddenWordLength; i++)
	{
		//compare letters against hidden word
		for (int32 j = 0; j < HiddenWordLength; j++)
		{
			//if they match in the same place, increment bulls
			if (tolower(Guess[j]) == MyHiddenWord[i])
			{
				if (i == j)
				{
					BullCowCount.Bulls++;
				}
				else
				{
					BullCowCount.Cows++;
				}
				
			}
	
		}

	}
	return BullCowCount;
}


