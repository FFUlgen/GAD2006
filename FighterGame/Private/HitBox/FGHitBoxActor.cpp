// Fill out your copyright notice in the Description page of Project Settings.


#include "HitBox/FGHitBoxActor.h"


AFGHitBoxActor::AFGHitBoxActor()
{
	PrimaryActorTick.bCanEverTick = true;

	HitBoxDamage = 0.f;
	HitStunTime = 0.f;
	BlockStunTime = 0.f;
	PushBackDistance = 0.f;
	LaunchDistance = 0.f;
}

void AFGHitBoxActor::TriggerVisualizeHitbox()
{
}


void AFGHitBoxActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void AFGHitBoxActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

