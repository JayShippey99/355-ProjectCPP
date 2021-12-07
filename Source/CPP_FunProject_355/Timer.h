// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/TextRenderComponent.h"
#include "Timer.generated.h"

UCLASS()
class CPP_FUNPROJECT_355_API ATimer : public AActor
{
	GENERATED_BODY()

		
public:	
	// Sets default values for this actor's properties
	ATimer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame // oh wait I thought it meant the whole thing was called every frame, just this function
	virtual void Tick(float DeltaTime) override;
	// so does this only get run once?? all this code?
	// or does it run at all?
	// is this just the page to be referenced?
	UPROPERTY()
	int32 CountdownTime;
	UTextRenderComponent* CountdownText;
	void UpdateTimerDisplay();

	void AdvanceTimer(); // okay so this is the function that counts time down

	void CountdownHasFinished(); // this is the function we do when the timer ends

	FTimerHandle CountdownTimerHandle; //THIS is the timer handle to control it
	// could i name this as anything? probably	// well actually that's weird it looks like this is setting up the variable, so this can be named anything
	// but how does it do anything when it does //clearTimer.(thing) in the other page?
};
