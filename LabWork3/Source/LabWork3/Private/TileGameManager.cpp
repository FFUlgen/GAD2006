// Fill out your copyright notice in the Description page of Project Settings.


#include "TileGameManager.h"

#include "TilePlayerController.h"

ATileGameManager::ATileGameManager() :
	GridSize(100),
	GridOffset(0,0,0.5f),
	MapExtendsInGrids(16)

{
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	GridSelection = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GridMesh"));
	GridSelection->SetupAttachment(RootComponent);

	CurrentSelectedTile = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CurrentSelectedTile"));
	CurrentSelectedTile->SetupAttachment(GridSelection);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> PlaneMesh(TEXT("StaticMesh'/Engine/BasicShapes/Plane.Plane'"));

	static ConstructorHelpers::FObjectFinder<UMaterialInterface> GridMaterial(TEXT("Material'/Game/UI/MAT_GridSlot.MAT_GridSlot'"));


	GridSelection->SetStaticMesh(PlaneMesh.Object);
	GridSelection->SetMaterial(0, GridMaterial.Object);
	GridSelection->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	CurrentSelectedTile->SetCollisionEnabled(ECollisionEnabled::NoCollision);

}

void ATileGameManager::BeginPlay()
{
	Super::BeginPlay();
	
	if (auto PlayerController = Cast<ATilePlayerController>(GWorld->GetFirstPlayerController()))
	{
		PlayerController->GameManager = this;
		CurentTileForGame();
	}
}

// Called every frame
void ATileGameManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATileGameManager::OnActorInteraction(AActor* HitActor, FVector& Location, bool IsPressed)
{
	
	if (TileTypes.Num() == 0) return;

	FVector GridLoc = GridOffset;
	GridLoc.X = FMath::GridSnap(Location.X, GridSize);
	GridLoc.Y = FMath::GridSnap(Location.Y, GridSize);
	GridLoc.Z = Location.Z;

	UPlayerInput* Input = GWorld->GetFirstPlayerController()->PlayerInput;	

	if (Input->WasJustPressed(EKeys::LeftMouseButton))
	{
		int GridX = GridLoc.X / GridSize + MapExtendsInGrids;
		int GridY = GridLoc.Y / GridSize + MapExtendsInGrids;

		if (GridX < 0 || GridY < 0 || GridX >= MapExtendsInGrids * 2 || GridY >= MapExtendsInGrids * 2)
		{
			return;
		}

		
		if (Map[GridX][GridY] != nullptr) return;

		if (TileTypes.IsValidIndex(CurentTileForGameIndex))
		{
			ATileBase* SelectedTile = TileTypes[CurentTileForGameIndex];
			Map[GridX][GridY] = SelectedTile;
			FTransform PreviewTileDirectionform(GridLoc + GridOffset);
			  
			PreviewTileDirectionform = FTransform(GetActorRotation(), PreviewTileDirectionform.GetLocation(), PreviewTileDirectionform.GetScale3D());
			SelectedTile->InstancedMesh->AddInstance(SelectedTile->InstancedMesh->GetRelativeTransform() * PreviewTileDirectionform, true);
		}
		
		UE_LOG(LogTemp, Warning, TEXT("Hit: %s - %f, %f, %f"), HitActor ? *HitActor->GetActorLabel() : TEXT("None"), Location.X, Location.Y, Location.Z);
	}

	

	else if (Input->WasJustPressed(EKeys::MouseScrollDown))
	{
		CurentTileForGameIndex = (CurentTileForGameIndex + 1) % TileTypes.Num();
		UE_LOG(LogTemp, Warning, TEXT("TileType: %s"), *TileTypes[CurentTileForGameIndex]->GetActorLabel());
		CurentTileForGame();

	}
	
	else if (Input->WasJustPressed(EKeys::MouseScrollUp))
	{
		if (CurentTileForGameIndex == 0)
		{
			CurentTileForGameIndex = TileTypes.Num();
		}

		CurentTileForGameIndex = (CurentTileForGameIndex - 1) % TileTypes.Num();
		UE_LOG(LogTemp, Warning, TEXT("TileType: %s"), *TileTypes[CurentTileForGameIndex]->GetActorLabel());
		CurentTileForGame();
	}
	
	else if (Input->WasJustPressed(EKeys::RightMouseButton))
	{
		PreviewTileDirection = (PreviewTileDirection + 90) % 360;
		SetActorRotation(FRotator(0, GetActorRotation().Yaw + PreviewTileDirection, 0));
	}
	else
	{
		GridSelection->SetWorldLocation(GridLoc + GridOffset);
		CurrentSelectedTile->SetWorldLocation(GridSelection->GetComponentLocation());
	}

}


void ATileGameManager::CurentTileForGame()
{
	CurrentSelectedTile->SetStaticMesh(TileTypes[CurentTileForGameIndex]->InstancedMesh->GetStaticMesh());
	CurrentSelectedTile->SetRelativeScale3D(TileTypes[CurentTileForGameIndex]->InstancedMesh->GetRelativeScale3D());
}



