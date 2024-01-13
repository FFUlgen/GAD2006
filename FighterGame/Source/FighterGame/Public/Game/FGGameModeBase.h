// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "FGGameModeBase.generated.h"

class AFGCharacterBase;


/**
 * 
 */
UCLASS()
class FIGHTERGAME_API AFGGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	AFGGameModeBase();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player References")
	AFGCharacterBase* player1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player References")
	AFGCharacterBase* player2;
};
