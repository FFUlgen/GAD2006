// Fill out your copyright notice in the Description page of Project Settings.


#include "NetPlayerState.h"
#include "ANetBaseCharacter.h"
#include "Net/UnrealNetwork.h"

void ANetPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ANetPlayerState, Data);
	DOREPLIFETIME(ANetPlayerState, PlayerIndex);
}

void ANetPlayerState::OnRep_PlayerInfo()
{
	AANetBaseCharacter* Char = Cast<AANetBaseCharacter>(GetPawn());
	if (Char)
	{
		Char->PlayerInfoReceived = true;
	}
	else
	{
		FTimerHandle PlayerInfoUpdateTimer;
		GWorld->GetTimerManager().SetTimer(PlayerInfoUpdateTimer, this, &ANetPlayerState::OnRep_PlayerInfo, 0.25f, false);
	}
}
