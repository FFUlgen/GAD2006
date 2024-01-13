// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/MutantCharacter.h"

AMutantCharacter::AMutantCharacter()
{
	PrimaryActorTick.bCanEverTick = true; 
}

void AMutantCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AMutantCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMutantCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}
