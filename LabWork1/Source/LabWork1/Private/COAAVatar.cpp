// Fill out your copyright notice in the Description page of Project Settings.


#include "COAAVatar.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

ACOAAVatar::ACOAAVatar() :
	Stamina(0.f),
	MaxStamina(100.f),
	StaminaGainRate(0.1f),
	StaminaDrainRate(0.25),
	RunSpeed(800.f),
	bStaminaDrained(false),
	bRunning(false)
{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->TargetArmLength = 300.f;
	SpringArm->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
	
	Camera->bUsePawnControlRotation = false;
	SpringArm->bUsePawnControlRotation = true;
	bUseControllerRotationYaw = true;
	Stamina = MaxStamina;
	
}

void ACOAAVatar::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Turn", this, &ACharacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &ACharacter::AddControllerPitchInput);
	
	PlayerInputComponent->BindAxis("MoveForward", this, &ACOAAVatar::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ACOAAVatar::MoveRight);

	PlayerInputComponent->BindAction("Jump", IE_Pressed,this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAction("Run", IE_Pressed, this, &ACOAAVatar::RunPressed);
	PlayerInputComponent->BindAction("Run", IE_Released, this, &ACOAAVatar::RunReleased);
}

void ACOAAVatar::MoveForward(float value)
{
	FRotator Rotation = GetController()->GetControlRotation();
	FRotator YawRotation(0.0f, Rotation.Yaw, 0.0f);
	FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	AddMovementInput(ForwardDirection, value);

}

void ACOAAVatar::MoveRight(float value)
{
	FRotator Rotation = GetController()->GetControlRotation();
	FRotator YawRotation(0.0f, Rotation.Yaw, 0.0f);
	FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	AddMovementInput(RightDirection, value);
}

void ACOAAVatar::RunPressed()
{
	bRunning = true;
	UpdateMovementParams();
	
	
}

void ACOAAVatar::RunReleased()
{
	
	bRunning = false;
	UpdateMovementParams();
	
}

void ACOAAVatar::UpdateMovementParams()
{
	GetCharacterMovement()->MaxWalkSpeed = bRunning && !bStaminaDrained ? RunSpeed : WalkSpeed;
}

void ACOAAVatar::Tick(float DeltaTime)
{
	UE_LOG(LogTemp, Warning, TEXT("Your Stamina = %f ") , Stamina);
	
	if (GetCharacterMovement()->MovementMode == EMovementMode::MOVE_Walking) 
	{
		if (bRunning && !bStaminaDrained) 
		{
			if (!GetCharacterMovement()->Velocity.IsNearlyZero(0.01)) 
			{
				Stamina = FMath::Max(0.0f, Stamina - StaminaDrainRate * DeltaTime);
				if (Stamina == 0.0f) 
				{
					bStaminaDrained = true;
					UpdateMovementParams();
				}
			}
		}
		else
		{
			{
				Stamina = FMath::Min(MaxStamina, Stamina + StaminaGainRate * DeltaTime);
				if (Stamina >= MaxStamina) 
				{
					bStaminaDrained = false;
					UpdateMovementParams();
				}
			}
		}
	}
	GEngine->AddOnScreenDebugMessage(0, DeltaTime, FColor::Red, FString::Printf(TEXT("Stamina %f"), Stamina));
}
