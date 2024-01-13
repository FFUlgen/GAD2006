// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FGCharacterBase.h"
#include "MutantCharacter.generated.h"

/**
 * 
 */
UCLASS()
class FIGHTERGAME_API AMutantCharacter : public AFGCharacterBase
{
	GENERATED_BODY()
public:
	AMutantCharacter();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
