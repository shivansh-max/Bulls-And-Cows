 // Fill out your copyright notice in the Description page of Project Settings.
#include "./BullCowCartridge.h"
#include "./HiddenWordList.h"

// Game begins
void UBullCowCartridge::BeginPlay() // When the game starts
{
	// When game starts to play
	Super::BeginPlay();

	Isograms = GetWords(Words);


	// Starting the game and setting the values
	SetUpGame();

}

// Inittilizing the game
void UBullCowCartridge::SetUpGame()
{
	// Setting the Word, Lives, Length, and the Game-Over to false
	// I am randomly generating a number then accsessing that index in the valid words
	int32 RandomIndex = FMath::RandRange(0, Isograms.Num() - 1);
	HiddenWord = Isograms[RandomIndex];
	Lives = HiddenWord.Len();
	Length = HiddenWord.Len();
	bGameOver = false;			

	// Informing the player
	PrintLine(TEXT("Welcome To Bull And Cow!!!"));
	PrintLine(TEXT("Guess the %i letter word !!!"), Length);
	PrintLine(TEXT("You have %i lives."), Lives);
	PrintLine(TEXT("Press Enter To Continue ..."));

	/*
		Debug Lines
		PrintLine(TEXT("There are %i total words."), Words.Num());
		PrintLine(TEXT("The word is %s !!!"), *HiddenWord);		                         
		PrintLine(TEXT("The amount of valid words %i"), GetWords(Words).Num());
	*/
}

// To end the game
void UBullCowCartridge::EndGame()
{
	// Setting Game-Over to true
	bGameOver = true;

	//Telling them what the hidden word is
	PrintLine(TEXT("The hidden word was %s"), *HiddenWord);

	// Waiting for player to play again
	PrintLine(TEXT("Press enter to play again..."));
}

// When you enter the input
// When the player hits enter		
void UBullCowCartridge::OnInput(const FString& Input)
{
	// Proccessing guess
	CheckGuess(Input);
}

// Function to check weather it is a isogram or not
bool UBullCowCartridge::IsIsogram(const FString& Word) const
{
	/*
		MEATHOD : Nested loop
		TIME = O(n^2)
		DEMO WORD : cat
		Loop through word once var = i 
		Loop through word twice var = j
		i = c; j = a; j = t
		i = a; j = t
		i = t;
		If match found return true else return false
	*/

	// First loop
	for (int32 i = 0; i < Word.Len(); i++)
	{
		// Second loop
		for (int32 j = i + 1; j < Word.Len(); j++)
		{
			// If statment to check if it works
			if (Word[i] == Word[j])
			{
				// Returning false because word is not a isogram
				return false;
			}
		}
	}


	// Returning true because the word is a isogram
	return true;
}

// Function to check the guess
void UBullCowCartridge::CheckGuess(const FString& Guess)
{
	// Checking if the game is over
	if (bGameOver)
	{
		// Clearing the screen for the player
		ClearScreen();

		// Starting the game and setting the values
		SetUpGame();

		// Early return for better complexity
		return;
	}

	// Checking if player won
	if (Guess == HiddenWord)
	{
		//Notifying player
		PrintLine(TEXT("Congrats You Win !!!"));

		// Ending game
		EndGame();

		// Early return for better complexity
		return;
	}

	// Checking if it is a Isogram
	if (!IsIsogram(Guess))
	{
		// Reminding the player that the word is a isogram
		PrintLine("No repeating characters in the word guess again !");

		// Early return for better complexityn
		return;
	}

	// Checking if player added right number of characters
	if (Guess.Len() != HiddenWord.Len())
	{
		// Reminding the player how long the word is
		PrintLine(TEXT("Sorry try again the word is\n%i letters long"), Length);

		// Early return for better complexity
		return;
	}

	// If the player has entered the correct length of word then dock a life
	--Lives;
	PrintLine(TEXT("You lost a life :("));
	PrintLine(TEXT("You have %i lives left"), Lives);

	// if player is dead
	if (Lives <= 0)
	{
		// Notifying the player
		PrintLine(TEXT("Sorry You Lost the game."), Length);

		// Ending the game
		EndGame();

		// Early return for better complexity
		return;
	}

	// Show Bulls and Cows
	// Creating the vars
	int32 Bull, Cow;
	
	// Getting the Bulls and Cows
	GetBullCow(Guess, Bull, Cow);

	PrintLine(TEXT("You have %i bulls and %i cows"), Bull, Cow);
}

// Getting words
TArray<FString> UBullCowCartridge::GetWords(const TArray<FString>& WordsList) const 
{	
	// New array with valid words
	TArray<FString> ValidWords;

	// Looping through the words to find valid words
	for (FString word: WordsList)      
	{
		// Seeing if the word is valid and it is in a good length
		if (word.Len() >= 4 && word.Len() <= 8 && IsIsogram(word))
		{
			// Adding it to the valid words
			ValidWords.Emplace(word);
		}
	}	

	// Returning the valid words.
	return ValidWords;
}

// Getting Bull Cows
void UBullCowCartridge::GetBullCow(const FString& Guess, int32& Bull, int32& Cow) const
{
	// Initilizing the variables
	Bull = 0;
	Cow = 0;

	// Going throgh the Guess
	for (int g = 0; g < Guess.Len(); g++)
	{
		// If it is a cow then adding and then finishing current itteration
		if (Guess[g] == HiddenWord[g])
		{
			// Adding a Bull
			Bull ++;
			// Finishing Current itteration
			continue;
		}

		// Looping through word to see if there are any cows
		for (int h = 0; h < HiddenWord.Len(); ++h)
		{
			// Found cow
			if (Guess[g] == HiddenWord[h])
			{
				// Adding a cow
				Cow ++;
				// Breaking
				break;
			}
		}
	}
}