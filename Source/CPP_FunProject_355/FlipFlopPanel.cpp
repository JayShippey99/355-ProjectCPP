// Fill out your copyright notice in the Description page of Project Settings.


#include "FlipFlopPanel.h"

// Sets default values
AFlipFlopPanel::AFlipFlopPanel()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//TheRoot = CreateDefaultSubobject<USceneComponent>(FName("TheRoot"));
	//RootComponent = TheRoot;
	//TheRoot->SetupAttachment(RootComponent);

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	hinge = CreateDefaultSubobject<USceneComponent>(FName("the hinge"));
	hinge->SetupAttachment(RootComponent);

	collider = CreateDefaultSubobject<UBoxComponent>(FName("the collider"));
	collider->SetupAttachment(hinge);

	platform = CreateDefaultSubobject<UStaticMeshComponent>(FName("the platform"));
	platform->SetupAttachment(hinge);

	PlatformAnim = CreateDefaultSubobject<UTimelineComponent>(TEXT("PlatformTimeline")); // the text is the internal name for it, nick doesn't know where it gets used though

	ConstructorHelpers::FObjectFinder<UStaticMesh> TheCubeMesh(TEXT("/Game/Art/Meshes/1M_Cube")); // lets use this to get our cyl

	if (TheCubeMesh.Succeeded()) { // or thecubemesh.object
		platform->SetStaticMesh(TheCubeMesh.Object);
		//hinge->SetStaticMesh(TheCubeMesh.Object);
	}
	//TheCubeMesh.Object



}

void AFlipFlopPanel::OnAnimUpdate(float val) { // the value of the curve is being sent in 

	//FVector forward = GetActorForwardVector()


	FRotator rot(val * 180, 0, 0); // fix this another day


	//if (isFlipped) rot *= -1; // we really wanna get this to work. I guess we 
	// why isn't this working now??
	hinge->SetRelativeRotation(FRotator(rot));
}

// Called when the game starts or when spawned
void AFlipFlopPanel::BeginPlay()
{
	Super::BeginPlay();

	InputComponent = NewObject<UInputComponent>(this);
	InputComponent->RegisterComponent();
	//... setup bindings:
	auto& binding = InputComponent->BindAction("FlipFlop", EInputEvent::IE_Pressed, this, &AFlipFlopPanel::Flip);
	binding.bConsumeInput = false;

	EnableInput(UGameplayStatics::GetPlayerController(GetWorld(), 0));

	//if (!InputComponent == NULL) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Blue, "Existing!");
	
	if (platformFlipCurve) { // if its not null..

		FOnTimelineFloat eventHandler;
		eventHandler.BindUFunction(this, TEXT("OnAnimUpdate")); // i think this is the function

		PlatformAnim->AddInterpFloat(platformFlipCurve, eventHandler, TEXT("Handle curve func")); // what is the function?
		PlatformAnim->SetTimelineLengthMode(ETimelineLengthMode::TL_LastKeyFrame); // set to use last keyframe
	}
}

// Called every frame
void AFlipFlopPanel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AFlipFlopPanel::OnConstruction(const FTransform& xform)
{
	Super::OnConstruction(xform); // what is the xform



	platform->SetWorldScale3D(FVector(platformSize, platformSize, platformThickness) / 100);
	platform->SetRelativeLocation(FVector(platformSize / 2, 0, 0));

	//hinge->SetWorldScale3D(FVector(platformSize, platformThickness + 5, platformThickness + 5) / 100);


	//hinge->SetRelativeLocation(FVector(-platformSize / 2, 0, 0));

	FVector platSize = FVector(platformSize, platformSize, platformThickness) / 2;

	//doorSize.X += 25;
	//doorSize.Y += 25;

	collider->SetBoxExtent(platSize);
	collider->SetRelativeLocation(FVector(platformSize / 2, 0, 0));
}

/*
void AFlipFlopPanel::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	//Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	

	InputComponent->BindAction("Flip", IE_Pressed, this, &AFlipFlopPanel::Flip);
	// weird these guys don't have IE pressed and released
}
*/

void AFlipFlopPanel::Flip()
{
	//if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Purple, "FLIP!");


	if (isOpen) {

		PlatformAnim->Reverse();
		isOpen = false;
	}
	/**/else {

		PlatformAnim->Play();
		isOpen = true;
	}
}