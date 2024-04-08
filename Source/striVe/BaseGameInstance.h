// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "BaseGameInstance.generated.h"

UENUM(BlueprintType)
enum class ECharacterClass : uint8
{
	VE_Default				UMETA(DisplayName = "Mannequin"),
	VE_FastCharacter		UMETA(DisplayName = "FastCharacter"),
	VE_StrongCharacter		UMETA(DisplayName = "StrongCharacter"),
	VE_GrapplerCharacter	UMETA(DisplayName = "GrapplerCharacter")
};

UCLASS()
class STRIVE_API UBaseGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player References")
		ECharacterClass P1CharacterClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player References")
		ECharacterClass P2CharacterClass;
};
