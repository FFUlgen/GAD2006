// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FGHitBoxActor.generated.h"

UENUM(BlueprintType)
enum class EHitBox : uint8
{
	HB_PROXIMITY   UMETA(DisplayName = "Proximity"),
	HB_STRIKE      UMETA(DisplayName = "Strike"),
	HB_HURTBOX     UMETA(DisplayName = "Hurtbox"),
};

UCLASS()
class FIGHTERGAME_API AFGHitBoxActor : public AActor
{
	GENERATED_BODY()
	
public:	
	
	AFGHitBoxActor();

	//Notify the BP_HitboxActor class instance that the hitbox is ready to be drawn.
	UFUNCTION(BlueprintCallable)
	void TriggerVisualizeHitbox();

	//Draw the hitbox to the screen to visualize it.
	UFUNCTION(BlueprintImplementableEvent)
	void VisualizeHitbox();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hitbox")
	EHitBox HitBoxType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, CaTegory = "Hitbox")
	FVector HitBoxLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, CaTegory = "Hitbox")
	float HitBoxDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, CaTegory = "Hitbox")
	float HitStunTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, CaTegory = "Hitbox")
	float BlockStunTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, CaTegory = "Hitbox")
	float PushBackDistance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, CaTegory = "Hitbox")
	float LaunchDistance;
protected:
	
	virtual void BeginPlay() override;

public:	
	
	virtual void Tick(float DeltaTime) override;

};
