// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "KZPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class KILLERZ_API AKZPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	virtual void Tick(float DeltaTime) override;
protected:
	virtual void BeginPlay() override;
private:

	void RotatePlayerToCursor();
};
