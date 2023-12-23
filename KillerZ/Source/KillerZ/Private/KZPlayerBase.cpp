// Fill out your copyright notice in the Description page of Project Settings.


#include "KZPlayerBase.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

AKZPlayerBase::AKZPlayerBase() 
{
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));

	SpringArm->SetupAttachment(GetMesh());
	Camera->SetupAttachment(SpringArm);
}

void AKZPlayerBase::BeginPlay()
{

}

void AKZPlayerBase::EnhancedInputMove(const FInputActionValue& Value)
{
}

void AKZPlayerBase::Tick(float DeltaTime)
{

}

void AKZPlayerBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}