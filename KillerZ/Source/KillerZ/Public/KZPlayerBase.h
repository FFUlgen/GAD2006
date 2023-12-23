// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "KZBaseCharacter.h"
#include "KZPlayerBase.generated.h"

/**
 * 
 */
UCLASS()
class KILLERZ_API AKZPlayerBase : public AKZBaseCharacter
{
	GENERATED_BODY()
	
public:
	AKZPlayerBase();

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

	void EnhancedInputMove(const class FInputActionValue& Value);
private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* SpringArm;
public:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enhanced Input")
	class UInputMappingContext* InputMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enhanced Input")
	class UInputAction* MoveInput;
};
