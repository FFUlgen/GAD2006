// Fill out your copyright notice in the Description page of Project Settings.


#include "KZPlayerBase.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Components/InputComponent.h"
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
	Super::BeginPlay();

	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(InputMappingContext, 0);
		}
	}
}

void AKZPlayerBase::EnhancedInputMove(const FInputActionValue& Value)
{
	const FVector2D moveVector = Value.Get<FVector2D>();

	if (moveVector.X > 0.01 || moveVector.X < 0.01)
	{
		AddMovementInput(FVector::ForwardVector, moveVector.X);
	}
	if (moveVector.Y > 0.01 || moveVector.Y < 0.01)
	{
		AddMovementInput(FVector::RightVector, moveVector.Y);
	}
}

void AKZPlayerBase::Tick(float DeltaTime)
{

}

void AKZPlayerBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	EnhancedInputComponent->BindAction(MoveInput, ETriggerEvent::Triggered, this, &AKZPlayerBase::EnhancedInputMove);
}