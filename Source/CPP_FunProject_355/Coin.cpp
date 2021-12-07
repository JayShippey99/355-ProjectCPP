// Fill out your copyright notice in the Description page of Project Settings.


#include "Coin.h"
#include "DrawDebugHelpers.h"
#include "Components/SphereComponent.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
ACoin::ACoin()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Creating default Components
	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere")); // this is the collision sphere

	sphereRadius = 20.0f;
	SphereComp->InitSphereRadius(sphereRadius);
	SphereComp->SetCollisionProfileName("Trigger"); // this must be what I was missing before
	RootComponent = SphereComp;

	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	StaticMeshComp->SetupAttachment(RootComponent);
	//ParticleComp = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleComp"));

	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &ACoin::OnOverlapBegin); // this &ADestroy... function does not exist yet

	//Attaching the Components and setting physics
	//SphereComp->SetupAttachment(RootComponent);
	//SphereComp->SetSimulatePhysics(true); // so we get "sphere comp" and set physics.
	//SphereComp->SetCollisionEnabled(ECollisionEnabled::NoCollision); // the physics colision system
	//SphereComp->SetEnableGravity(true); // gonna disable gravity too

	StaticMeshComp->AttachToComponent(SphereComp, FAttachmentTransformRules::KeepRelativeTransform); // okay so we attach one thing to another here
	//ParticleComp->AttachToComponent(StaticMeshComp, FAttachmentTransformRules::KeepRelativeTransform);

	//Setting the Sphere radius to be of a smaller size in line with the Static Mesh.
	SphereComp->SetSphereRadius(16.0f);

	//Setting the Static Mesh Scale and Location to fit the radius of the Sphere.
	StaticMeshComp->SetRelativeLocation(FVector(0.0, 0.0, -12.0f));
	StaticMeshComp->SetRelativeScale3D(FVector(0.25, 0.25, 0.25));

	// setting up collision now
}

// Called when the game starts or when spawned
void ACoin::BeginPlay()
{
	Super::BeginPlay();

	InputComponent = NewObject<UInputComponent>(this);
	InputComponent->RegisterComponent();
	//... setup bindings:
	InputComponent->BindAction("Interact", EInputEvent::IE_Pressed, this, &ACoin::TellMeNews);


}

// Called every frame
void ACoin::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	RootComponent->AddRelativeRotation(FRotator(0, 2, 0));

	//DrawDebugSphere(GetWorld(), GetActorLocation(), 20, 20, FColor::Red, false, -1, 0, 1); // no idea what this does really // oh wait never mind its doing like a line trace but a sphere

}

void ACoin::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
	{
		Destroy();
	}
}

void ACoin::TellMeNews()
{
	if(GEngine) GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Blue, "Existing!");
}



