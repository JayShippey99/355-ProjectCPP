// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Coin.generated.h"

UCLASS()
class CPP_FUNPROJECT_355_API ACoin : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ACoin();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class USphereComponent* SphereComp; //  so we create a sphere component here, this is the collider

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* StaticMeshComp; // a mesh component here

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UMaterial* CoinMaterial;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
		//class UParticleSystemComponent* ParticleComp; // a particle component here

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void TellMeNews();

	float sphereRadius;

	UFUNCTION() // looks like if we wanted we could call this anything, cool
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
