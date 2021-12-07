// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Pawn.h"
#include "Components/TimelineComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "InteractableThing.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "Components/BoxComponent.h"
#include "Components/InputComponent.h"

#include "FlipFlopPanel.generated.h"




UCLASS()
class CPP_FUNPROJECT_355_API AFlipFlopPanel : public AActor // s, public IInteractableThing
{
	GENERATED_BODY()






public:
	// Sets default values for this actor's properties

	// all this stuff below me, not sure why it can go in the bottom public function
	// scene component for root
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		//class USceneComponent* TheRoot;
	// scene component for hinge
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		//class USceneComponent* hinge;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		class UBoxComponent* collider;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		class UStaticMeshComponent* platform;
	// mesh for door frame
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		//class UInstancedStaticMeshComponent* TheMeshFrame;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Platform Dimensions")
		float platformSize = 200;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Platform Dimensions")
		float platformThickness = 10;

	// gonna create a curve asset for the timeline
	// we made the asset in unreal
	// we then created a blueprint that we childed that from this cpp class
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Platform Dimensions")
		UCurveFloat* platformFlipCurve;

	// collider


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
		void OnAnimUpdate(float val);

	UPROPERTY()
	UTimelineComponent* PlatformAnim;

public:
	AFlipFlopPanel(); // for some reason putting this here rather than above worked

	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void OnConstruction(const FTransform& xform) override;
	//virtual void Interact();

	//virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	float flipDirection = 1;
	float flipRate = 1;
	float currentRotation = 0;

	bool isFlipped = false;
	bool isOpen = false;
	//virtual void Interact();

	UFUNCTION()
		void Flip();

};
