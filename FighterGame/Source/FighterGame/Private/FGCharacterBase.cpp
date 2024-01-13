// Fill out your copyright notice in the Description page of Project Settings.


#include "FGCharacterBase.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "Engine/Engine.h"
#include "Game/FGGameModeBase.h"

// Sets default values
AFGCharacterBase::AFGCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.f);

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	GetCharacterMovement()->bOrientRotationToMovement = false;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 720.f, 0.f);
	GetCharacterMovement()->GravityScale = 2.f;
	GetCharacterMovement()->AirControl = 0.80f;
	GetCharacterMovement()->JumpZVelocity = 1000.f;
	GetCharacterMovement()->GroundFriction = 3.f;
	GetCharacterMovement()->MaxWalkSpeed = 400.f;
	GetCharacterMovement()->MaxFlySpeed = 600.f;

	HurtBox = nullptr;
	OtherPlayer = nullptr;
	CharacterState = ECharacterState::VE_Default;
	Transform = FTransform();
	Scale = FVector(0.f, 0.f, 0.f);

	PlayerHealth = 1.f;
	MaxDistanceApart = 1000.f;
	StunTime = 0.f;
	gravityScale = GetCharacterMovement()->GravityScale;
	SuperMeterAmount = 0.f;
	removeInputFromBufferTime = 1.f;

	CanMove = false;
	LightAttackUsed = false;
	MediumAttackUsed = false;
	SpecialAttackUsed = false;
	isFlipped = false; 
	HasLandedHit = false;
	CanUseSpecialAttack = true;

	CharacterCommands.SetNum(2);
	// Command 1
	CharacterCommands[0].name = "Command #1";
	CharacterCommands[0].inputs.Add("A");
	CharacterCommands[0].inputs.Add("B");
	CharacterCommands[0].inputs.Add("C");
	CharacterCommands[0].hasUsedCommand = false;
	//Command 2
	CharacterCommands[1].name = "Command #2";
	CharacterCommands[1].inputs.Add("1");
	CharacterCommands[1].inputs.Add("2");
	CharacterCommands[1].inputs.Add("3");
	CharacterCommands[1].hasUsedCommand = false;
}

// Called when the game starts or when spawned
void AFGCharacterBase::BeginPlay()
{
	Super::BeginPlay();
}

void AFGCharacterBase::MoveRight(float value)
{
	if (CanMove && CharacterState != ECharacterState::VE_Crouching && CharacterState != ECharacterState::VE_Blocking)
	{
		FVector Direction = FVector::ForwardVector;
		UE_LOG(LogTemp, Warning, TEXT("The directional input is: %f"), value);
		if (CharacterState != ECharacterState::VE_Jumping && CharacterState != ECharacterState::VE_Launched)
		{
			if (value > 0.1f)
			{
				CharacterState = ECharacterState::VE_MovingRight;
			}
			else if (value < -0.1f)
			{
				CharacterState = ECharacterState::VE_MovingLeft;

			}
			else
			{
				CharacterState = ECharacterState::VE_Default;
			}
		}
		

		float currentDistanceApart = abs(OtherPlayer->GetActorLocation().X - GetActorLocation().X);

		if (currentDistanceApart >= MaxDistanceApart)
		{
			if ((currentDistanceApart + value < currentDistanceApart && isFlipped) || (currentDistanceApart - value < currentDistanceApart && !isFlipped))
			{
				AddMovementInput(Direction, value);
			}
			
		}
		else
		{
			AddMovementInput(Direction, value);
		}
	}
	
}

void AFGCharacterBase::MoveRightController(float value)
{
	if (CanMove && CharacterState != ECharacterState::VE_Crouching && CharacterState != ECharacterState::VE_Blocking)
	{
		FVector Direction = FVector::ForwardVector;
		UE_LOG(LogTemp, Warning, TEXT("The directional input is: %f"), value);
		if (CharacterState != ECharacterState::VE_Jumping && CharacterState != ECharacterState::VE_Launched)
		{
			if (value > 0.55f)
			{
				CharacterState = ECharacterState::VE_MovingRight;
			}
			else if (value < -0.55f)
			{
				CharacterState = ECharacterState::VE_MovingLeft;

			}
			else
			{
				CharacterState = ECharacterState::VE_Default;
			}
		}


		float currentDistanceApart = abs(OtherPlayer->GetActorLocation().X - GetActorLocation().X);

		if (currentDistanceApart >= MaxDistanceApart)
		{
			if ((currentDistanceApart + value < currentDistanceApart && isFlipped) || (currentDistanceApart - value < currentDistanceApart && !isFlipped))
			{
				AddMovementInput(Direction, value);
			}

		}
		else
		{
			AddMovementInput(Direction, value);
		}
	}
}

void AFGCharacterBase::BeginStun()
{
	CanMove = false;
	GetWorld()->GetTimerManager().SetTimer(StunTH, this, &AFGCharacterBase::EndStun, StunTime, false);
}

void AFGCharacterBase::EndStun()
{
	if (CharacterState != ECharacterState::VE_Launched)
	{
		CharacterState = ECharacterState::VE_Default;
	}
	CanMove = true;
}

void AFGCharacterBase::AddInputToInputBuffer(FInputInfo inputInfo)
{
	inputBuffer.Add(inputInfo);
	CheckInputBufferForCommand();
}

void AFGCharacterBase::RemoveInputFromInputBuffer()
{
}

void AFGCharacterBase::CheckInputBufferForCommand()
{
	int correctSequenceCounter = 0;
	for (auto currentCommand : CharacterCommands)
	{
		for (int commandInput = 0; commandInput < currentCommand.inputs.Num(); ++commandInput)
		{
			for (int input = 0; input < inputBuffer.Num(); ++input)
			{
				if (input + correctSequenceCounter < inputBuffer.Num())
				{
					if (inputBuffer[input + correctSequenceCounter].inputName.Compare(currentCommand.inputs[commandInput]) == 0)
					{
						UE_LOG(LogTemp, Warning, TEXT("The player added another input to the command sequence"));
						++correctSequenceCounter;

						if (correctSequenceCounter == currentCommand.inputs.Num())
						{
							StartCommand(currentCommand.name);
						}
						break;
					}
					else
					{
						UE_LOG(LogTemp, Warning, TEXT("The player broke the command sequence"));
						correctSequenceCounter = 0;
					}

				}
				else
				{
					UE_LOG(LogTemp, Warning, TEXT("The player is not yet finished with the command sequence"));
					correctSequenceCounter = 0;
				}
			}
		}
	}
	
}

void AFGCharacterBase::StartCommand(FString commandName)
{
	for (int currentCommand = 0; currentCommand < CharacterCommands.Num(); ++currentCommand)
	{
		if (commandName.Compare(CharacterCommands[currentCommand].name) == 0)
		{
			UE_LOG(LogTemp, Warning, TEXT("The character is using the command: %s."), *commandName);
			CharacterCommands[currentCommand].hasUsedCommand = true;
		}

	}
}

void AFGCharacterBase::StartBlocking()
{
	CharacterState = ECharacterState::VE_Blocking;
}

void AFGCharacterBase::StopBlocking()
{
	CharacterState = ECharacterState::VE_Default;

}

void AFGCharacterBase::CollidedWithProximityHitbox()
{
}

void AFGCharacterBase::TakeDamage(float DamageAmount, float stunTime, float blockStunTime, float pushBackAmount, float launchAmount)
{
	if (CharacterState != ECharacterState::VE_Blocking)
	{
		PlayerHealth -= DamageAmount;
		SuperMeterAmount += DamageAmount * 0.85;

		CharacterState = ECharacterState::VE_Stunned;
		StunTime = stunTime;
		if (stunTime > 0.0f)
		{
			CharacterState = ECharacterState::VE_Stunned;
			BeginStun();
		}

		if (OtherPlayer)
		{
			OtherPlayer->HasLandedHit = true;
			OtherPlayer->PerformPushBack(0.0f, 0.f, false);

			if(!OtherPlayer->SpecialAttackUsed)
			{
				OtherPlayer->SuperMeterAmount += DamageAmount * 5;
			}
		}
		PerformPushBack(pushBackAmount, launchAmount, false);
	}
	else
	{
		float reducedDamage = DamageAmount * 0.5;
		PlayerHealth -= reducedDamage;

		StunTime = blockStunTime;
		if (StunTime > 0.f)
		{
			BeginStun();
		}
		else
		{
			CharacterState = ECharacterState::VE_Default;
		}
		if (OtherPlayer)
		{
			OtherPlayer->HasLandedHit = true;
			OtherPlayer->PerformPushBack(0.0f, 0.f, false);
		}
		PerformPushBack(pushBackAmount, 0.f, true);
	}
	if (PlayerHealth < 0.f)
	{
		PlayerHealth = 0.f;
	}
}

void AFGCharacterBase::PerformPushBack(float pushBackAmount, float launchAmount, bool hasBlocked)
{
	if (hasBlocked)
	{
		if (isFlipped)
		{
			LaunchCharacter(FVector(pushBackAmount * 2.0f, 0.f, 0.f), false, false);
		}
		else
		{
			LaunchCharacter(FVector(-pushBackAmount * 2.0f, 0.f, 0.f), false, false);
		}
	}
	else
	{
		if (launchAmount > 0.f)
		{
			GetCharacterMovement()->GravityScale *= 0.7;
			CharacterState = ECharacterState::VE_Launched;
		}
		if (isFlipped)
		{
			LaunchCharacter(FVector(pushBackAmount, 0.f, launchAmount), false, false);
		}
		else
		{
			LaunchCharacter(FVector(-pushBackAmount, 0.f, launchAmount), false, false);
		}
	}
}

void AFGCharacterBase::Jump()
{
	if(CanMove)
	{
		ACharacter::Jump();
		CharacterState = ECharacterState::VE_Jumping;
	}
	
}

void AFGCharacterBase::StopJumping()
{
	ACharacter::StopJumping();
}

void AFGCharacterBase::Landed(const FHitResult& Hit)
{
	if (CharacterState == ECharacterState::VE_Launched || CharacterState == ECharacterState::VE_Jumping)
	{
		GetCharacterMovement()->GravityScale = gravityScale;
		CharacterState = ECharacterState::VE_Default;
	}
	//ACharacter::Landed(Hit);
}

void AFGCharacterBase::StartCrouching()
{
	
	CharacterState = ECharacterState::VE_Crouching;

}

void AFGCharacterBase::StopCrouching()
{
	CharacterState = ECharacterState::VE_Default;
}

void AFGCharacterBase::StartAttack1()
{
	UE_LOG(LogTemp, Warning, TEXT("We are using our light attack."));
	LightAttackUsed = true;
}

void AFGCharacterBase::StartAttack2()
{
	UE_LOG(LogTemp, Warning, TEXT("We are using our medium attack."));
	MediumAttackUsed = true;
}

void AFGCharacterBase::StartSpecialAttack()
{
	
	UE_LOG(LogTemp, Warning, TEXT("We are using our special attack."));
	if (SuperMeterAmount >= 1)
	{
		SpecialAttackUsed = true;
	}
	
}

// Called every frame
void AFGCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (CharacterState != ECharacterState::VE_Jumping)
	{
		if (OtherPlayer)
		{
			if (auto characterMovement = GetCharacterMovement())
			{
				if (auto enemyMovement = OtherPlayer->GetCharacterMovement())
				{
					if (enemyMovement->GetActorLocation().X >= characterMovement->GetActorLocation().X)
					{
						if (isFlipped)
						{
							if (auto mesh = GetCapsuleComponent()->GetChildComponent(1))
							{
								Transform = mesh->GetRelativeTransform();
								Scale = Transform.GetScale3D();
								Scale.Y = 1.f;
								Transform.SetScale3D(Scale);
								mesh->SetRelativeTransform(Transform);
							}
							isFlipped = false;
						}
					}
					else
					{
						if (!isFlipped)
						{
							if (auto mesh = GetCapsuleComponent()->GetChildComponent(1))
							{
								Transform = mesh->GetRelativeTransform();
								Scale = Transform.GetScale3D();
								Scale.Y = -1.f;
								Transform.SetScale3D(Scale);
								mesh->SetRelativeTransform(Transform);
							}
							isFlipped = true;
						}
					}
				}
			}

		}
	}
	
}

// Called to bind functionality to input
void AFGCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	/*if (auto gameMode = Cast<AFGGameModeBase>(GetWorld()->GetAuthGameMode()))
	{
		if (gameMode->player1 == this)
		{
			PlayerInputComponent->BindAxis("MoveRight", this, &AFGCharacterBase::MoveRight);
		}
		else
		{
			PlayerInputComponent->BindAxis("MoveRightController", this, &AFGCharacterBase::MoveRight);
		}
	}*/
	
	PlayerInputComponent->BindAxis("MoveRight", this, &AFGCharacterBase::MoveRight);
	//PlayerInputComponent->BindAxis("MoveRightController", this, &AFGCharacterBase::MoveRightController);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AFGCharacterBase::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &AFGCharacterBase::StopJumping);
	PlayerInputComponent->BindAction("Block", IE_Pressed, this, &AFGCharacterBase::StartBlocking);
	PlayerInputComponent->BindAction("Block", IE_Released, this, &AFGCharacterBase::StopBlocking);
	PlayerInputComponent->BindAction("Crouch", IE_Pressed, this, &AFGCharacterBase::StartCrouching);
	PlayerInputComponent->BindAction("Crouch", IE_Released, this, &AFGCharacterBase::StopCrouching);
	PlayerInputComponent->BindAction("Attack1", IE_Pressed, this, &AFGCharacterBase::StartAttack1);
	PlayerInputComponent->BindAction("Attack2", IE_Pressed, this, &AFGCharacterBase::StartAttack2);
	PlayerInputComponent->BindAction("SpecialAttack", IE_Pressed, this, &AFGCharacterBase::StartSpecialAttack);
	
	

}

