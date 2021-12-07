// Fill out your copyright notice in the Description page of Project Settings.


#include "Timer.h"

// Sets default values
ATimer::ATimer()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	CountdownText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("CountdownNumber"));
	CountdownText->SetHorizontalAlignment(EHTA_Center);
	CountdownText->SetWorldSize(150.0f);
	RootComponent = CountdownText;
	CountdownTime = 3;
}

// Called when the game starts or when spawned
void ATimer::BeginPlay()
{
	Super::BeginPlay();
	UpdateTimerDisplay();
	GetWorldTimerManager().SetTimer(CountdownTimerHandle, this, &ATimer::AdvanceTimer, 1.0f, true);
}

// Called every frame
void ATimer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATimer::UpdateTimerDisplay()
{
	CountdownText->SetText(FString::FromInt(FMath::Max(CountdownTime, 0))); // this sets the thing visually as 3 to start I think
	//CountdownText->SetText(TEXT("Hello"));
}

void ATimer::AdvanceTimer()
{
	--CountdownTime;
	UpdateTimerDisplay();
	if (CountdownTime < 1)
	{
		// we're done running, so stop the timer. but how does this do anything
		GetWorldTimerManager().ClearTimer(CountdownTimerHandle); // clear timer I assume clears a timer thing
		CountdownHasFinished();
	}
}

void ATimer::CountdownHasFinished()
{
	CountdownText->SetText(TEXT("Go!"));
}

