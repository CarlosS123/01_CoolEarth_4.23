// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "CoolEarthGameMode.h"
#include "CoolEarthPlayerController.h"
#include "CoolEarthCharacter.h"
#include "UObject/ConstructorHelpers.h"

ACoolEarthGameMode::ACoolEarthGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = ACoolEarthPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDownCPP/Blueprints/TopDownCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}