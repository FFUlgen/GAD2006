// Fill out your copyright notice in the Description page of Project Settings.


#include "NetGameMode.h"
#include "ANetBaseCharacter.h"

ANetGameMode::ANetGameMode()
{
	DefaultPawnClass = AANetBaseCharacter::StaticClass();
}
