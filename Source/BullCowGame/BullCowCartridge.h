// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "./CoreMinimal.h"
#include "./Console/Cartridge.h"
#include "BullCowCartridge.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BULLCOWGAME_API UBullCowCartridge : public UCartridge
{
	GENERATED_BODY()

	public:
	virtual void BeginPlay() override;
	virtual void OnInput(const FString& Input) override;
	void SetUpGame();
	void EndGame();
	void GetBullCow(const FString& Guess, int32& Bull, int32& Cow) const;
	void CheckGuess(const FString& Guess);
	bool IsIsogram(const FString& Word) const;
	TArray<FString> GetWords(const TArray<FString>& WordsList) const;

	// Your declarations go below!
	private:
	TArray<FString> Isograms;
	FString HiddenWord;
	int32 Lives;
	int32 Length;

    bool bGameOver;
};
