// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "striVeCharacter.h"
#include "striVeGameMode.generated.h"


UCLASS(minimalapi)
class AstriVeGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AstriVeGameMode();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player References")
		AstriVeCharacter* player1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player References")
		AstriVeCharacter* player2;
};