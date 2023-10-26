// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CoABaseCharacter.h"
#include "COAAVatar.generated.h"

/**
 * a
 */
UCLASS()
class LABWORK1_API ACOAAVatar : public ACoABaseCharacter
{
	GENERATED_BODY()
public:
	ACOAAVatar();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character")
	class UCameraComponent* Camera;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character")
	class USpringArmComponent* SpringArm;

	UPROPERTY(EditAnywhere, Category = "COA")
	float RunSpeed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "COA")
	float Stamina;
	UPROPERTY(EditAnywhere, Category = "COA")
	float MaxStamina;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "COA")
	float StaminaGainRate;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "COA")
	float StaminaDrainRate;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "COA")
	bool bStaminaDrained;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "COA")
	bool bRunning;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
private:
	void MoveForward(float value);
	void MoveRight(float value);
	void RunPressed();
	void RunReleased();
	void UpdateMovementParams();
protected:
public:
	virtual void Tick(float DeltaTime) override;
};

