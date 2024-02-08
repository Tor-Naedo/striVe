// Copyright Epic Games, Inc. All Rights Reserved.

#include "striVeCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

AstriVeCharacter::AstriVeCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate when the controller rotates.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Create a camera boom attached to the root (capsule)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true); // Rotation of the character should not affect rotation of boom
	CameraBoom->bDoCollisionTest = false;
	CameraBoom->TargetArmLength = 500.f;
	CameraBoom->SocketOffset = FVector(0.f,0.f,75.f);
	CameraBoom->SetRelativeRotation(FRotator(0.f,180.f,0.f));

	// Create a camera and attach to boom
	SideViewCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("SideViewCamera"));
	SideViewCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	SideViewCameraComponent->bUsePawnControlRotation = false; // We don't want the controller rotating the camera

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Face in the direction we are moving..
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->GravityScale = 2.f;
	GetCharacterMovement()->AirControl = 0.80f;
	GetCharacterMovement()->JumpZVelocity = 1000.f;
	GetCharacterMovement()->GroundFriction = 3.f;
	GetCharacterMovement()->MaxWalkSpeed = 600.f;
	GetCharacterMovement()->MaxFlySpeed = 600.f;

	playerHealth = 1.00f;
	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)
}

//////////////////////////////////////////////////////////////////////////
// Input

void AstriVeCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// set up gameplay key bindings
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	PlayerInputComponent->BindAxis("MoveRight", this, &AstriVeCharacter::MoveRight);

	PlayerInputComponent->BindAction("Attack1", IE_Pressed, this, &AstriVeCharacter::StartAttack1);
	//PlayerInputComponent->BindAction("Attack1", IE_Released, this, &AstriVeCharacter::StopAttack1); 
	PlayerInputComponent->BindAction("Attack2", IE_Pressed, this, &AstriVeCharacter::StartAttack2);
	//PlayerInputComponent->BindAction("Attack2", IE_Released, this, &AstriVeCharacter::StopAttack2); 
	PlayerInputComponent->BindAction("Attack3", IE_Pressed, this, &AstriVeCharacter::StartAttack3);
	//PlayerInputComponent->BindAction("Attack3", IE_Released, this, &AstriVeCharacter::StopAttack3); 
	PlayerInputComponent->BindAction("Attack4", IE_Pressed, this, &AstriVeCharacter::StartAttack4);
	//PlayerInputComponent->BindAction("Attack4", IE_Released, this, &AstriVeCharacter::StopAttack4); 

	PlayerInputComponent->BindTouch(IE_Pressed, this, &AstriVeCharacter::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &AstriVeCharacter::TouchStopped);
}

void AstriVeCharacter::MoveRight(float Value)
{
	// add movement in that direction
	AddMovementInput(FVector(0.f,-1.f,0.f), Value);
}

void AstriVeCharacter::TouchStarted(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	// jump on any touch
	Jump();
}

void AstriVeCharacter::TouchStopped(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	StopJumping();
}

void AstriVeCharacter::StartAttack1()
{
	UE_LOG(LogTemp, Warning, TEXT("Using attack 1"));
	wasFirstAttackUsed = true;
}

void AstriVeCharacter::StartAttack2()
{
	UE_LOG(LogTemp, Warning, TEXT("Using attack 2"));
}

void AstriVeCharacter::StartAttack3()
{
	UE_LOG(LogTemp, Warning, TEXT("Using attack 3"));
}

void AstriVeCharacter::StartAttack4()
{
	UE_LOG(LogTemp, Warning, TEXT("Using attack 4"));
	TakeDamage(0.05f);
}

void AstriVeCharacter::TakeDamage(float _damageAmount)
{
	UE_LOG(LogTemp, Warning, TEXT("Taking Damage"), _damageAmount);
	playerHealth -= _damageAmount;

	if (playerHealth < 0.00f)
	{
		playerHealth = 0.00f;
	}
}
