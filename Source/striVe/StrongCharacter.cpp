// Fill out your copyright notice in the Description page of Project Settings.


#include "StrongCharacter.h"

// Sets default values
AStrongCharacter::AStrongCharacter()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	characterClass = ECharacterClass::VE_StrongCharacter;
}

// Called when the game starts or when spawned
void AStrongCharacter::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AStrongCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

//Notify the HitboxActorBp class instance that the hitbox is ready to be drawn.
void AStrongCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

