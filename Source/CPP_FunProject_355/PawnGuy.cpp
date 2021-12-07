// Fill out your copyright notice in the Description page of Project Settings.

#include "PawnGuy.h" // this up here is like parenting stuff from the h page
#include "Camera/CameraComponent.h"

// Sets default values
APawnGuy::APawnGuy()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	// create a camera and a visible object
	UCameraComponent* OurCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("OurCamera"));
	OurVisibleComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("OurVisibleComponent")); // yeah this is where we set up the static mesh thing
	// so is creating a subobject literally like.... idk what its doing exactly
	// do we need this now? we are already seting th visibleComp as a static mesh
	// idk we do it in the door so lets keep it here


	// attach the camera and visible object to the root component. offset and rotate the camera.
	OurCamera->SetupAttachment(RootComponent);
	OurCamera->SetRelativeLocation(FVector(-250.0f, 0.0f, 250.0f)); // hm so it seems like doing -> is what gets us node functions
	OurCamera->SetRelativeRotation(FRotator(-45.0f, 0.0f, 0.0f));
	OurVisibleComponent->SetupAttachment(RootComponent);

	ConstructorHelpers::FObjectFinder<UStaticMesh> CylinderMesh(TEXT("/Engine/BasicShapes/Cylinder")); // lets use this to get our cyl

	if (CylinderMesh.Succeeded())
	{
		OurVisibleComponent->SetStaticMesh(CylinderMesh.Object);
	}
}

// Called when the game starts or when spawned
void APawnGuy::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APawnGuy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	float CurrentScale = RootComponent->GetComponentScale().X;
	if (bGrowing)
	{
		CurrentScale += (DeltaTime * 2.0f);
	}
	else CurrentScale -= (DeltaTime * 1.0f);

	CurrentScale = FMath::Clamp(CurrentScale, 1.0f, 2.0f);
	RootComponent->SetRelativeScale3D(FVector(CurrentScale));
	//pawnHeight = CurrentScale;
	// so here's the thing, we are scaling the root component, so the camera will move accordingly, just scaling 
	// its scaling in the middle of the mesh rather than on the root

	if (!CurrentVelocity.IsZero())
	{
		FVector NewLocation = GetActorLocation() + (CurrentVelocity * DeltaTime);
		SetActorLocation(NewLocation);
	}

	//OurVisibleComponent->SetRelativeLocation(FVector(0, 0, pawnHeight / 2)); // pawn heigth isn't changing that's the thing, but why is it not scaling on the dot? who knows

}

// Called to bind functionality to input
void APawnGuy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) // when does this run?? // maybe this just runs on its own??
{
	Super::SetupPlayerInputComponent(PlayerInputComponent); // weird so if the visibleComp is a static mesh, this breaks // WAIT is this where it was??
	// no wait this mustve already been broken
	// wtf once this compiled it went fine

	InputComponent->BindAction("Grow", IE_Pressed, this, &APawnGuy::StartGrowing); // weird, startgrowing doesn't need ()
	InputComponent->BindAction("Grow", IE_Released, this, &APawnGuy::StopGrowing);

	InputComponent->BindAxis("MoveForward", this, &APawnGuy::Move_XAxis); // weird, startgrowing doesn't need ()
	InputComponent->BindAxis("MoveRight", this, &APawnGuy::Move_YAxis);
	// weird these guys don't have IE pressed and released
}

void APawnGuy::OnConstruction(const FTransform& xform) // so the & symbol isn't like actually saying, this and that
{
	Super::OnConstruction(xform); // wonder what happens without this

	OurVisibleComponent->SetWorldScale3D(FVector(pawnWidth, pawnWidth, pawnHeight) / 100);
	OurVisibleComponent->SetRelativeLocation(FVector(0, 0, pawnHeight / 2));

	//AH it worked fuck yeah
}

void APawnGuy::Move_XAxis(float AxisValue)
{
	CurrentVelocity.X = FMath::Clamp(AxisValue, -1.0f, 1.0f) * 300.0f;
}

void APawnGuy::Move_YAxis(float AxisValue)
{
	CurrentVelocity.Y = FMath::Clamp(AxisValue, -1.0f, 1.0f) * 300.0f;
}

void APawnGuy::StartGrowing()
{
	bGrowing = true;
}

void APawnGuy::StopGrowing()
{
	bGrowing = false;
}


