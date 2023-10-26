// Fill out your copyright notice in the Description page of Project Settings.


#include "CoABaseCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
ACoABaseCharacter::ACoABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CharacterMovementComponent = GetCharacterMovement();

	bDead = false;
	Health = 100.f;
	MaxHealth = 100.f;
	HealingRate = 0.f;
	WalkSpeed = 300.f;


	CharacterMovementComponent->bOrientRotationToMovement = true;
	CharacterMovementComponent->RotationRate = FRotator(0.0f, 540.0f, 0.0f);
	CharacterMovementComponent->MaxWalkSpeed = WalkSpeed;
}

// Called when the game starts or when spawned
void ACoABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACoABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!bDead) 
	{
		Health = FMath::Min(MaxHealth, Health + HealingRate * DeltaTime);
		
	}

}

// Called to bind functionality to input
void ACoABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

