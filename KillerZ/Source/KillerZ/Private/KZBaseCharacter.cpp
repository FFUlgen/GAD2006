// Fill out your copyright notice in the Description page of Project Settings.


#include "KZBaseCharacter.h"


AKZBaseCharacter::AKZBaseCharacter()
{
 	
	PrimaryActorTick.bCanEverTick = false;
	MaxHP = 100.f;
	MovementSpeed = 300.f;
	AttackSpeed = 1.f;
	AttackCooldown = 2;
	AttackDamage = 2;
}

void AKZBaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	CurrentHP = MaxHP;
	
}

void AKZBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AKZBaseCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) 
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}




