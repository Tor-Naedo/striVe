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
	//CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	//CameraBoom->SetupAttachment(RootComponent);
	//CameraBoom->SetUsingAbsoluteRotation(true); // Rotation of the character should not affect rotation of boom
	//CameraBoom->bDoCollisionTest = false;
	//CameraBoom->TargetArmLength = 500.f;
	//CameraBoom->SocketOffset = FVector(0.f,0.f,75.f);
	//CameraBoom->SetRelativeRotation(FRotator(0.f,180.f,0.f));

	// Create a camera and attach to boom
	//SideViewCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("SideViewCamera"));
	//SideViewCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	//SideViewCameraComponent->bUsePawnControlRotation = false; // We don't want the controller rotating the camera

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Face in the direction we are moving..
GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f); // ...at this rotation rate
GetCharacterMovement()->GravityScale = 2.f;
GetCharacterMovement()->AirControl = 0.80f;
GetCharacterMovement()->JumpZVelocity = 1000.f;
GetCharacterMovement()->GroundFriction = 3.f;
GetCharacterMovement()->MaxWalkSpeed = 600.f;
GetCharacterMovement()->MaxFlySpeed = 600.f;
GetCharacterMovement()->bOrientRotationToMovement = false;

otherPlayer = nullptr;
hurtbox = nullptr;
playerHealth = 1.00f;
wasFirstAttackUsed = false;
isFlipped = false;
maxDistanceApart = 800.0f;
// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)
}

//////////////////////////////////////////////////////////////////////////
// Input

void AstriVeCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	//if(auto gameMode = Cast<AstriVeGameMode>(GetWorldChecked()->GetAuthGameMode()))
	// set up gameplay key bindings
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AstriVeCharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &AstriVeCharacter::StopJumping);
	PlayerInputComponent->BindAxis("MoveRight", this, &AstriVeCharacter::MoveRight);
	PlayerInputComponent->BindAction("Crouch", IE_Pressed, this, &AstriVeCharacter::StartCrouching);
	PlayerInputComponent->BindAction("Crouch", IE_Released, this, &AstriVeCharacter::StopCrouching);
	PlayerInputComponent->BindAction("Block", IE_Pressed, this, &AstriVeCharacter::StartBlocking);
	PlayerInputComponent->BindAction("Block", IE_Released, this, &AstriVeCharacter::StopBlocking);

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

void AstriVeCharacter::Jump()
{
	ACharacter::Jump();
	characterState = ECharacterState::VE_Jumping;
}

//
//void AstriVeCharacter::StopJumping()
//{
	//ACharacter::StopJumping;
//}

void AstriVeCharacter::Landed(const FHitResult& Hit)
{
	characterState = ECharacterState::VE_Default;
}

void AstriVeCharacter::StartCrouching()
{
	isCrouching = true;
}

void AstriVeCharacter::StopCrouching()
{
	isCrouching = false;
}

void AstriVeCharacter::StartBlocking()
{
	characterState = ECharacterState::VE_Blocking;
}

void AstriVeCharacter::StopBlocking()
{
	characterState = ECharacterState::VE_Default;
}

void AstriVeCharacter::MoveRight(float Value)
{
	if (!isCrouching && characterState != ECharacterState::VE_Blocking)
	{
		UE_LOG(LogTemp, Warning, TEXT("The directional input is %f"), Value);

	if (characterState != ECharacterState::VE_Jumping)
	{
		if (Value > 0.20f)
		{
			characterState = ECharacterState::VE_MovingRight;
		}
		else if (Value < -0.20f)
		{
			characterState = ECharacterState::VE_MovingLeft;
		}
		else
		{
			characterState = ECharacterState::VE_Default;
		}
	}

	float currentDistanceApart = abs(otherPlayer->GetActorLocation().Y - GetActorLocation().Y);

	if (currentDistanceApart >= maxDistanceApart)
	{
		if ((currentDistanceApart + Value < currentDistanceApart && !isFlipped) || (currentDistanceApart - Value < currentDistanceApart && isFlipped))
		{
			// add movement in that direction
			AddMovementInput(FVector(0.0f, 1.0f, 0.0f), Value);
		}
	}
	else
	{
		// add movement in that direction
		AddMovementInput(FVector(0.0f, 1.0f, 0.0f), Value);
	}
	}
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
	wasSecondAttackUsed = true;
}

void AstriVeCharacter::StartAttack3()
{
	UE_LOG(LogTemp, Warning, TEXT("Using attack 3"));
	wasThirdAttackUsed = true;
}

void AstriVeCharacter::StartAttack4()
{
	UE_LOG(LogTemp, Warning, TEXT("Using attack 4"));
	wasFourthAttackUsed = true;
}

void AstriVeCharacter::P2KeyboardAttack1()
{
	StartAttack1();
}

void AstriVeCharacter::P2KeyboardAttack2()
{
	StartAttack2();
}

void AstriVeCharacter::P2KeyboardAttack3()
{
	StartAttack3();
}

void AstriVeCharacter::P2KeyboardAttack4()
{
	StartAttack4();
}

void AstriVeCharacter::P2KeyboardJump()
{
	// jump on any touch
	Jump();
}

void AstriVeCharacter::P2KeyboardStopJumping()
{
	StopJumping();
}

void AstriVeCharacter::P2KeyboardMoveRight(float _value)
{
	MoveRight(_value);
}

void AstriVeCharacter::TakeDamage(float _damageAmount)
{
	if (characterState != ECharacterState::VE_Blocking)
	{
		UE_LOG(LogTemp, Warning, TEXT("We are taking damage for %f points."), _damageAmount);
		playerHealth -= _damageAmount;

		PlayDamageSoundEffect();
	}
	else
	{
		float reducedDamage = _damageAmount * 0.5f;
		UE_LOG(LogTemp, Warning, TEXT("We are taking reduced damage for %f points."), reducedDamage);
		playerHealth -= reducedDamage;
	}
	if (playerHealth < 0.00f)
	{
		playerHealth = 0.00f;
	}
}

//NEEDS FIXING I THINK
// Called every frame.
void  AstriVeCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (otherPlayer)
	{
		if (auto characterMovement = GetCharacterMovement())
		{
			if (auto enemyMovement = otherPlayer->GetCharacterMovement())
			{
				if (enemyMovement->GetActorLocation().Y <= characterMovement->GetActorLocation().Y)
				{
					if (isFlipped)
					{
						if (auto mesh = GetCapsuleComponent()->GetChildComponent(1))
						{
							transform = mesh->GetRelativeTransform();
							scale = transform.GetScale3D();
							scale.Y = -1;
							transform.SetScale3D(scale);
							mesh->SetRelativeTransform(transform);
						}
						isFlipped = false;
					}
				}
				else
				{
					if (!isFlipped)
					{
						if (auto mesh = GetCapsuleComponent()->GetChildComponent(1))
						{
							transform = mesh->GetRelativeTransform();
							scale = transform.GetScale3D();
							scale.Y = 1;
							transform.SetScale3D(scale);
							mesh->SetRelativeTransform(transform);
						}
						isFlipped = true;
					}
				}
			}
		}
	}
}