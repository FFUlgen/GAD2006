// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "GameSlot.generated.h"

USTRUCT(Blueprintable)
struct FSGridPosition
{
	GENERATED_USTRUCT_BODY();

	FSGridPosition() {}
	FSGridPosition(uint8 col, uint8 row) :
		Col(col),
		Row(row) {}

	UPROPERTY(EditAnywhere)
	uint8 Col;

	UPROPERTY(EditAnywhere)
	uint8 Row;
};
UENUM(Blueprintable)
enum EGridState
{
	GS_Default,
	GS_Highlighted,
	GS_Offensive,
	GS_Supportive
};

UCLASS()
class AGameSlot : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGameSlot();

	UPROPERTY(BluePrintReadWrite)
	FSGridPosition GridPosition;

	UPROPERTY(EditAnywhere)
	UBoxComponent* Box;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Plane;

	UFUNCTION()
	void SetState(EGridState NewState);

private:
	
	EGridState GridState;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
