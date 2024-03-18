// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "striVeCharacter.generated.h"

UENUM(BlueprintType)
enum class ECharacterState : uint8
{
	VE_Default			UMETA(DisplayName =	"NOT_MOVING"),
	VE_MovingRight		UMETA(DisplayName =	"MOVING_RIGHT"),
	VE_MovingLeft		UMETA(DisplayName =	"MOVING_LEFT"),
	VE_Jumping			UMETA(DisplayName =	"JUMPING"),
	VE_Blocking			UMETA(DisplayName = "Blocking")
};

UCLASS(config=Game)
class AstriVeCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Side view camera */
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	//class UCameraComponent* SideViewCameraComponent;

	/** Camera boom positioning the camera beside the character */
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	//class USpringArmComponent* CameraBoom;

	void StartAttack1();
	void StartAttack2();
	void StartAttack3();
	void StartAttack4();

	//When in Keyboard-Only Mode, use these functions to perform actions with Player 2.
	UFUNCTION(BlueprintCallable)
		void P2KeyboardAttack1();

	UFUNCTION(BlueprintCallable)
		void P2KeyboardAttack2();

	UFUNCTION(BlueprintCallable)
		void P2KeyboardAttack3();

	UFUNCTION(BlueprintCallable)
		void P2KeyboardAttack4();

	UFUNCTION(BlueprintCallable)
		void P2KeyboardJump();

	UFUNCTION(BlueprintCallable)
		void P2KeyboardStopJumping();

	UFUNCTION(BlueprintCallable)
		void P2KeyboardMoveRight(float _value);

protected:

	/** Called for side to side input */
	void MoveRight(float Val);

	/** Handle touch inputs. */
	void TouchStarted(const ETouchIndex::Type FingerIndex, const FVector Location);

	/** Handle touch stop event. */
	void TouchStopped(const ETouchIndex::Type FingerIndex, const FVector Location);

	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
	
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	//ECharacterClass characterClass;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//the direction the character is moving OR the direction the player is holding down
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
		ECharacterState characterState;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player References")
		AstriVeCharacter* otherPlayer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hitbox")
		AActor* hurtbox;

	//The caharacter's transform
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Model")
		FTransform transform;

	//The character's scale
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Model")
		FVector scale;

	//The maximum amount of distance that the players can be apart
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
		float maxDistanceApart;

	//Override the ACharacter and APawn functionality to have more control over jumps and landings
	virtual void Jump() override;
	//virtual void StopJumping()override;
	virtual void Landed(const FHitResult& Hit) override;

	//Make the character begin crouching
	UFUNCTION(BlueprintCallable)
		void StartCrouching();

	//Make the character stop crouching
	UFUNCTION(BlueprintCallable)
		void StopCrouching();

	//Make the character begin blocking
	UFUNCTION(BlueprintCallable)
		void StartBlocking();

	//Make the character stop blocking
	UFUNCTION(BlueprintCallable)
		void StopBlocking();

	//Damage the player.
	UFUNCTION(BlueprintCallable)
		void TakeDamage(float _damageAmount);

	//Make the Character Sound
	UFUNCTION(BlueprintImplementableEvent)
		void PlayDamageSoundEffect();

	//Has the player used the LPunch Attack?
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attacks")
		bool wasFirstAttackUsed;

	//Has the player used the RPunch Attack?
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attacks")
		bool wasSecondAttackUsed;

	//Has the player used the LKick Attack?
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attacks")
		bool wasThirdAttackUsed;

	//Has the player used the RKick Attack?
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attacks")
		bool wasFourthAttackUsed;

	//The amount of health the character currently has
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
		float playerHealth;

	//Is the character's model flipped?
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Model")
		bool isFlipped;

	//Is the character currently crouching
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
		bool isCrouching;

public:
	AstriVeCharacter();

	/** Returns SideViewCameraComponent subobject **/
	//FORCEINLINE class UCameraComponent* GetSideViewCameraComponent() const { return SideViewCameraComponent; }
	/** Returns CameraBoom subobject **/
	//FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
};
