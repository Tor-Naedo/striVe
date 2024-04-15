// Copyright Epic Games, Inc. All Rights Reserved.

#include "striVeGameMode.h"
#include "striVeCharacter.h"
#include "UObject/ConstructorHelpers.h"

AstriVeGameMode::AstriVeGameMode()
{

	//set the default values for variables
	numRounds = 3;
	roundTime = 99;
	isTimerActive = false;

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/SideScrollerCPP/Blueprints/SideScrollerCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
