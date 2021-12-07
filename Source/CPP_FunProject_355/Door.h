// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/TimelineComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "InteractableThing.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "Components/BoxComponent.h"

#include "Door.generated.h"




UCLASS()
class CPP_FUNPROJECT_355_API ADoor : public AActor, public IInteractableThing
{
	GENERATED_BODY()




	
	
public:	
	// Sets default values for this actor's properties
	ADoor();

	// all this stuff below me, not sure why it can go in the bottom public function
	// scene component for root
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class USceneComponent* TheRoot;
// scene component for hinge
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class USceneComponent* TheHinge;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UBoxComponent* Collider;

	
	// mesh for door
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UStaticMeshComponent* TheMeshDoor;
// mesh for door frame
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UInstancedStaticMeshComponent* TheMeshFrame;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Door Stats") // okay so we can literally create new category names, this is cool
		float WidthOfDoor = 200;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Door Stats")
		float HeightOfDoor = 400;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Door Stats")
		float DepthOfDoor = 25;

	// gonna create a curve asset for the timeline
	// we made the asset in unreal
	// we then created a blueprint that we childed that from this cpp class
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Door Stats")
	UCurveFloat* doorOpenCurve;

	// collider


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnAnimUpdate(float val);

	//UPROPERTY()
	UTimelineComponent* DoorAnim;

	bool IsDoorFlipped = false;
	bool IsDoorOpen = false;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void OnConstruction(const FTransform& xform) override;
	virtual void Interact();
};
