// Fill out your copyright notice in the Description page of Project Settings.
#include "./BullCowCartridge.h"

// Game begins
void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();

    // Starting the game and setting the values
    InitGame();

    // Debug Line
    PrintLine(TEXT("The word is %s !!!"), *HiddenWord);
}

// Inittilizing the game
void UBullCowCartridge::InitGame()
{
    // Setting the Word, Lives, Length, and the Game-Over to false
    HiddenWord = TEXT("Blanket");
    Lives = HiddenWord.Len();
    Length = HiddenWord.Len();
    bGameOver = false;

    // Informing the player
    PrintLine(TEXT("Welcome To Bull And Cow!!!"));
    PrintLine(TEXT("Guess the %i letter word !!!"), Length);
    PrintLine(TEXT("You have %i lives."), Lives);
    PrintLine(TEXT("Press Enter To Continue ..."));
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
void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{
    // Proccessing guess
    CheckGuess(Input);
}

// Function to check weather it is a isogram or not
bool UBullCowCartridge::IsIsogram(FString Word) const
{

    Reference
    // for (int32 i = 0; i < Word.Len(); i++)
    // {
    //     PrintLine(TEXT("%c"), Word[i]);
    //     // PrintLine(TEXT("TEXT"));
    // }

    return true;
}

// Function to check the guess
void UBullCowCartridge::CheckGuess(FString Guess)
{
    // Checking if the game is over
    if (bGameOver)
    {
        // Clearing the screen for the player
        ClearScreen();

        // Starting the game and setting the values
        InitGame();

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

    // Checking if it is a Isogram nnnnnnnnnnnnnnnnnnnnnnnnnv
    if (!IsIsogram(Guess))
    {
        // Reminding the player that the word is a isogram
        PrintLine("No repeating characters in the word guess again !");

        // Early return for better complexitynmmmmmmmmmmmmm
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
}
