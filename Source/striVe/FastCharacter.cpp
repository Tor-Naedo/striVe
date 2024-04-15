// Fill out your copyright notice in the Description page of Project Settings.
#include "FastCharacter.h"

// Sets default values
AFastCharacter::AFastCharacter()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	characterClass = ECharacterClass::VE_FastCharacter;

}

// Called when the game starts or when spawned
void AFastCharacter::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AFastCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

//Notify the HitboxActorBp class instance that the hitbox is ready to be drawn.
void AFastCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}
