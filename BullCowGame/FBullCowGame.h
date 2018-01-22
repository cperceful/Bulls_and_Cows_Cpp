#pragma once
#include <string>

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
	Non_Alpha_Characters,
};

class FBullCowGame
{
public:
	FBullCowGame();
	void Reset(); //make rich return value
	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;
	bool IsGameWon() const;
	EGuessStatus CheckGuessValidity(FString) const;
	FBullCowCount SubmitGuess(FString);

private:
	int32 MyMaxTries;
	int32 MyCurrentTry;
	FString MyHiddenWord;
};