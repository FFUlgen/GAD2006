// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "KZBaseCharacter.generated.h"

UCLASS()
class KILLERZ_API AKZBaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	
	AKZBaseCharacter();

protected:
	
	virtual void BeginPlay() override;

public:	

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float CurrentHP;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float MaxHP;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float MovementSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float AttackSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float AttackCooldown;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float AttackDamage;


};
