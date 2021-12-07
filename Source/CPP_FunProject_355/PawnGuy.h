// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h" // if I had to guesss, this is giving me the access to the input components and stuff // nope idk anymore
#include "UObject/ConstructorHelpers.h"

#include "PawnGuy.generated.h"

UCLASS()
class CPP_FUNPROJECT_355_API APawnGuy : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APawnGuy();

	// lets set up variables for the scale and size of our pawn
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pawn Dimensions");
	float pawnHeight = 200;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pawn Dimensions");
	float pawnWidth = 200; // we'll just one variable for this and then when we do the scaling just use this twice

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void OnConstruction(const FTransform& xform) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override; // this is where its set up but not run... right?? // does this override the super line in the cpp file?

	UPROPERTY(EditAnywhere) // UPROPERTY makes it visible to the engine
		class UStaticMeshComponent* OurVisibleComponent; // our visible component is the static mesh, but right now its a scene component, lets switch it to static mesh?
	// but ALSO, without uproperty we wouldn't be able to set it in the editor I believe
		// oh actually what happens is that it doesn't even show up in the components tab, interesting
	// okay so we needed to add class to the beginning of this for whatever reason


	// input functions
	void Move_XAxis(float AxisValue);
	void Move_YAxis(float AxisValue);
	void StartGrowing();
	void StopGrowing();

	FVector CurrentVelocity;
	bool bGrowing; // assuming this has a b at the front for bool
};
