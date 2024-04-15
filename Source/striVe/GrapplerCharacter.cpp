// Fill out your copyright notice in the Description page of Project Settings.


#include "GrapplerCharacter.h"

// Sets default values
AGrapplerCharacter::AGrapplerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	characterClass = ECharacterClass::VE_GrapplerCharacter;
}

// Called when the game starts or when spawned
void AGrapplerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGrapplerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AGrapplerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

