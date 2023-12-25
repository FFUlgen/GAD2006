// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "KZBaseCharacter.h"
#include "KZEnemyBase.generated.h"

/**
 * 
 */
UCLASS()
class KILLERZ_API AKZEnemyBase : public AKZBaseCharacter
{
	GENERATED_BODY()
public:
	AKZEnemyBase();
protected:
	virtual void BeginPlay() override;
private:

};
