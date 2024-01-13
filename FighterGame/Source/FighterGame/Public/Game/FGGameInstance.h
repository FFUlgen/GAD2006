// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "FGGameInstance.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class ECharacterClass : uint8
{
	VE_Default    UMETA(DisplayName = "Mannequin"),
	VE_Mutant     UMETA(DisplayName = "Mutant")
	//VE_NINJA      UMETA(DisplayName = "Ninja")
};

UCLASS()
class FIGHTERGAME_API UFGGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player References")
	ECharacterClass CharacterClass;
};
