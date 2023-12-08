// Fill out your copyright notice in the Description page of Project Settings.


#include "NetAvatar.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"


ANetAvatar::ANetAvatar() : MovementScale (1.0f)
{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
}

void ANetAvatar::BeginPlay()
{
	Super::BeginPlay();

	Camera->bUsePawnControlRotation = false;
	SpringArm->bUsePawnControlRotation = true;
	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->MaxWalkSpeed = 300.0f;
}

void ANetAvatar::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Turn", this, &ACharacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis("Lookup", this, &ACharacter::AddControllerPitchInput);

	PlayerInputComponent->BindAxis("MoveForward", this, &ANetAvatar::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ANetAvatar::MoveRight);
	PlayerInputComponent->BindAction("Run", EInputEvent::IE_Pressed, this, &ANetAvatar::RunPressed);
	PlayerInputComponent->BindAction("Run", EInputEvent::IE_Released, this, &ANetAvatar::RunReleased);
}


void ANetAvatar::MoveForward(float Amount)
{
	FRotator Rotation = GetController()->GetControlRotation();
	FRotator YawRotation(0.f, Rotation.Yaw, 0.f);
	FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	AddMovementInput(ForwardDirection, Amount * MovementScale);
}

void ANetAvatar::MoveRight(float Amount)
{
	FRotator Rotation = GetController()->GetControlRotation();
	FRotator YawRotation(0.f, Rotation.Yaw, 0.f);
	FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	AddMovementInput(ForwardDirection, Amount * MovementScale);
}

void ANetAvatar::RunPressed()
{
	if (HasAuthority())
	{
		bHoldingRunKey = true;
		UpdateMovementParams();
	}
	else
	{
		ServerStartRunning();
	}
}

void ANetAvatar::RunReleased()
{
	if (HasAuthority())
	{
		bHoldingRunKey = false;
		UpdateMovementParams();
	}
	else
	{
		ServerStopRunning();
	}
}

void ANetAvatar::UpdateMovementParams()
{
	if (bHoldingRunKey)
	{
		GetCharacterMovement()->MaxWalkSpeed = 600.0f;
	}
	else
	{
		GetCharacterMovement()->MaxWalkSpeed = 300.0f;
	}
}
void ANetAvatar::ServerStartRunning_Implementation()
{
	RunPressed();
}

void ANetAvatar::ServerStopRunning_Implementation()
{
	RunReleased();
}

