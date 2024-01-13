// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FGCharacterBase.generated.h"

UENUM(BlueprintType)
enum class ECharacterState : uint8
{
	VE_Default     UMETA(DisplayName = "NOT_MOVING"),
	VE_MovingRight UMETA(DisplayName = "MOVING_RIGHT"),
	VE_RunningRight UMETA(DisplayName = "RUNNING_RIGHT"),
	VE_MovingLeft  UMETA(DisplayName = "MOVING_LEFT"),
	VE_RunningLeft UMETA(DisplayName = "RUNNING_LEFT"),
	VE_Jumping     UMETA(DisplayName = "JUMPING"),
	VE_Stunned     UMETA(DisplayName = "STUNNED"),
	VE_Blocking    UMETA(DisplayName = "BLOCKING"),
	VE_Crouching   UMETA(DisplayName = "CROUCHING"),
	VE_Launched    UMETA(DisplayName = "LAUNCHED"),

};

USTRUCT(BlueprintType)
struct FCommand
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	FString name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	TArray<FString> inputs;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	bool hasUsedCommand;
};

USTRUCT(BlueprintType)
struct FInputInfo
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	FString inputName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	float timeStamp;
};

UCLASS()
class FIGHTERGAME_API AFGCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	AFGCharacterBase();
	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	virtual void BeginPlay() override;

	void MoveRight(float value);
	void MoveRightController(float value);

	void BeginStun();
	void EndStun();

	UFUNCTION(BlueprintCallable)
	void AddInputToInputBuffer(FInputInfo inputInfo);

	UFUNCTION(BlueprintCallable)
	void RemoveInputFromInputBuffer();

	//check if the input buffer contains any set from the character's list of commands
	UFUNCTION(BlueprintCallable)
	void CheckInputBufferForCommand();
	//make the character begin using a command based off of the command's name
	UFUNCTION(BlueprintCallable)
	void StartCommand(FString commandName);

	UFUNCTION(BlueprintCallable)
	void StartBlocking();
	UFUNCTION(BlueprintCallable)
	void StopBlocking();

	UFUNCTION(BlueprintCallable)
	void CollidedWithProximityHitbox();

	UFUNCTION(BlueprintCallable)
	void TakeDamage(float DamageAmount, float stunTime, float blockStunTime, float pushBackAmount, float launchAmount);

	void PerformPushBack(float pushBackAmount, float launchAmount, bool hasBlocked);

	virtual void Jump() override;
	virtual void StopJumping() override;
	virtual void Landed(const FHitResult& Hit) override;

	UFUNCTION()
	void StartCrouching();

	UFUNCTION()
	void StopCrouching();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player References")
	AFGCharacterBase* OtherPlayer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hitbox")
	AActor* HurtBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	ECharacterState CharacterState;

	//Characters Transform
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Model")
	FTransform Transform;

	//Characters Scale
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Model")
	FVector Scale;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	TArray<FInputInfo> inputBuffer;

	//Commands to be used when a correct series of inputs has been pressed
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category =  "Input")
	TArray<FCommand> CharacterCommands;

	FTimerHandle StunTH;
	FTimerHandle inputBufferTH;

	float removeInputFromBufferTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float PlayerHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float StunTime;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float gravityScale;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	float MaxDistanceApart;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Super Meter")
	float SuperMeterAmount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attacks")
	bool LightAttackUsed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attacks")
	bool MediumAttackUsed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attacks")
	bool SpecialAttackUsed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attacks")
	bool CanUseSpecialAttack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Model")
	bool isFlipped;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attacks")
	bool HasLandedHit;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	bool CanMove;

	

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DebugValue;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	//ECharacterClass CharacterClass;

private:
	void StartAttack1();
	void StartAttack2();
	void StartSpecialAttack();

public:

};
