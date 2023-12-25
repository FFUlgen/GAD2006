// Fill out your copyright notice in the Description page of Project Settings.


#include "KZPlayerController.h"
#include "Kismet/KismetMathLibrary.h"

void AKZPlayerController::Tick(float DeltaTime)
{
	RotatePlayerToCursor();	
}

void AKZPlayerController::BeginPlay()
{
	bShowMouseCursor = true;
}

void AKZPlayerController::RotatePlayerToCursor()
{
	FVector mousePos;
	FVector mouseDir;
	DeprojectMousePositionToWorld(mousePos, mouseDir);
	FHitResult HitResult;
	FVector Start = mousePos;
	FVector End = mousePos + 15000 * mouseDir;
	GWorld->LineTraceSingleByChannel(HitResult, Start, End, ECollisionChannel::ECC_WorldStatic);
	HitResult.ImpactPoint.Z = GetPawn()->GetActorLocation().Z;
	GetPawn()->SetActorRotation(UKismetMathLibrary::FindLookAtRotation(GetPawn()->GetActorLocation(), HitResult.ImpactPoint));
}
