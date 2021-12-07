// Fill out your copyright notice in the Description page of Project Settings.


#include "Door.h"

// Sets default values
ADoor::ADoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TheRoot = CreateDefaultSubobject<USceneComponent>(FName("TheRoot"));
	RootComponent = TheRoot;
	TheRoot->SetupAttachment(RootComponent);

	TheHinge = CreateDefaultSubobject<USceneComponent>(FName("TheHinge"));
	TheHinge->SetupAttachment(TheRoot);

	Collider = CreateDefaultSubobject<UBoxComponent>(FName("Box Collider"));
	Collider->SetupAttachment(TheRoot);

	TheMeshDoor = CreateDefaultSubobject<UStaticMeshComponent>(FName("TheMeshDoor"));
	TheMeshDoor->SetupAttachment(TheHinge);

	TheMeshFrame = CreateDefaultSubobject<UInstancedStaticMeshComponent>(FName("TheMeshFrame"));
	TheMeshFrame->SetupAttachment(TheRoot);

	DoorAnim = CreateDefaultSubobject<UTimelineComponent>(TEXT("DoorTimeline")); // the text is the internal name for it, nick doesn't know where it gets used though


	ConstructorHelpers::FObjectFinder<UStaticMesh> TheCubeMesh(TEXT("/Game/Art/Meshes/1M_Cube")); // lets use this to get our cyl
	
	if (TheCubeMesh.Succeeded()) { // or thecubemesh.object
		TheMeshDoor->SetStaticMesh(TheCubeMesh.Object);
		TheMeshFrame->SetStaticMesh(TheCubeMesh.Object);
	}
	//TheCubeMesh.Object

	
	
}

void ADoor::OnAnimUpdate(float val) {

	FRotator rot(0, val * 90, 0);

	if (IsDoorFlipped) rot.Yaw *= -1;

	TheHinge->SetRelativeRotation(FRotator(rot));
}

// Called when the game starts or when spawned
void ADoor::BeginPlay()
{
	Super::BeginPlay();
	
	if (doorOpenCurve) { // if its not null..

		FOnTimelineFloat eventHandler;
		eventHandler.BindUFunction(this, TEXT("OnAnimUpdate")); // i think this is the function

		DoorAnim->AddInterpFloat(doorOpenCurve, eventHandler, TEXT("Handle curve func")); // what is the function?
		DoorAnim->SetTimelineLengthMode(ETimelineLengthMode::TL_LastKeyFrame); // set to use last keyframe
	}
}

// Called every frame
void ADoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADoor::OnConstruction(const FTransform& xform)
{
	Super::OnConstruction(xform); // what is the xform

	TheMeshDoor->SetWorldScale3D(FVector(WidthOfDoor, DepthOfDoor, HeightOfDoor) / 100); // why do we do this? // oh wait, we set each thing as a number, but then /100 makes it equal a scale value for it

	TheMeshDoor->SetRelativeLocation(FVector(WidthOfDoor / 2, 0, HeightOfDoor / 2));
	TheHinge->SetRelativeLocation(FVector(-WidthOfDoor / 2, 0, 0));

	TheMeshFrame->ClearInstances();

	TheMeshFrame->AddInstance(FTransform(FRotator(0, 0, 0), FVector(WidthOfDoor / 2 + DepthOfDoor / 2, 0, HeightOfDoor / 2), FVector(DepthOfDoor, DepthOfDoor, HeightOfDoor) / 100));
	TheMeshFrame->AddInstance(FTransform(FRotator(0, 0, 0), FVector(-WidthOfDoor / 2 - DepthOfDoor / 2, 0, HeightOfDoor / 2), FVector(DepthOfDoor, DepthOfDoor, HeightOfDoor) / 100));


	FVector doorSize = FVector(WidthOfDoor, DepthOfDoor, HeightOfDoor) / 2;

	doorSize.X += 25;
	doorSize.Y += 25;

	Collider->SetBoxExtent(doorSize);
	Collider->SetRelativeLocation(FVector(0, 0, HeightOfDoor / 2));

}

void ADoor::Interact() // so how does this get triggered exactly?
{
	if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Orange, "Player Wants to Interact");


	if (IsDoorOpen) {

		DoorAnim->Reverse();
		IsDoorOpen = false;
	}
	else {
		// determine which side of the door the player is on
		// to set IsDoorFlipped
		// do Math!
		ACharacter* player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
		FVector vecToDoor = GetActorLocation() - player->GetActorLocation();
		vecToDoor.Normalize();

		float align = FVector::DotProduct(vecToDoor, GetActorRightVector());

		IsDoorFlipped = (align < 0); // woah this is really cool

		DoorAnim->Play();
		IsDoorOpen = true;
	}
}

