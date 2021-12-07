// Copyright Epic Games, Inc. All Rights Reserved.

#include "CPP_FunProject_355GameMode.h"
#include "CPP_FunProject_355Character.h"
#include "UObject/ConstructorHelpers.h"

ACPP_FunProject_355GameMode::ACPP_FunProject_355GameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
