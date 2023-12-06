// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ANetBaseCharacter.h"
#include "NetAvatar.generated.h"


UCLASS()
class ANetAvatar : public AANetBaseCharacter
{
	GENERATED_BODY()
public:

	ANetAvatar();

	UPROPERTY(EditAnywhere)
	class UCameraComponent* Camera;

	UPROPERTY(EditAnywhere)
	class USpringArmComponent* SpringArm;

	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
private:
	void MoveForward(float Amount);
	void MoveRight(float Amount);
};
