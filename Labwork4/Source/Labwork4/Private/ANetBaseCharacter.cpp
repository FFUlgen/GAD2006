// Fill out your copyright notice in the Description page of Project Settings.


#include "ANetBaseCharacter.h"
#include "NetGameInstance.h"
#include "NetPlayerState.h"

static UDataTable* SBodyParts = nullptr;

static const wchar_t* BodyPartNames[] =
{
	TEXT("Face"),
	TEXT("Hair"),
	TEXT("Chest"),
	TEXT("Hands"),
	TEXT("Legs"),
	TEXT("Beard"),
	TEXT("EyeBrows")
};
// Sets default values
AANetBaseCharacter::AANetBaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PartFace = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Face"));
	PartFace->SetupAttachment(GetMesh());
	PartFace->SetLeaderPoseComponent(GetMesh());

	PartHands = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Hands"));
	PartHands->SetupAttachment(GetMesh());
	PartHands->SetLeaderPoseComponent(GetMesh());

	PartLegs = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Legs"));
	PartLegs->SetupAttachment(GetMesh());
	PartLegs->SetLeaderPoseComponent(GetMesh());

	PartHair = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Hair"));
	PartHair->SetupAttachment(PartFace, FName("headSocket"));

	PartBeard = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Beard"));
	PartBeard->SetupAttachment(PartFace, FName("headSocket"));

	PartEyeBrows = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("EyeBrows"));
	PartEyeBrows->SetupAttachment(PartFace, FName("headSocket"));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SK_Eyes(TEXT("StaticMesh'/Game/StylizedModularChar/Meshes/SM_Eyes.SM_Eyes'"));

	PartEyes = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Eyes"));
	PartEyes->SetupAttachment(PartFace, FName("headSocket"));
	PartEyes->SetStaticMesh(SK_Eyes.Object);

	static ConstructorHelpers::FObjectFinder<UDataTable> DT_BodyParts(TEXT("DataTable'/Game/BLueprints/DT_BodyParts.DT_BodyParts'"));
	SBodyParts = DT_BodyParts.Object;
}

// Called when the game starts or when spawned
void AANetBaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	if (GetNetMode() == ENetMode::NM_Standalone) return;
	SetActorHiddenInGame(true);
	CheckPlayerState();
}

void AANetBaseCharacter::OnConstruction(const FTransform& Transform)
{
	UpdateBodyParts();
}

// Called every frame
void AANetBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FString AANetBaseCharacter::GetCustomizationData()
{
	FString Data;
	for (size_t i = 0; i < (int)EBodyPart::BP_COUNT; i++)
	{
		Data += FString::FromInt(BodyPartIndices[i]);
		if (i < ((int)(EBodyPart::BP_COUNT)-1)) Data += TEXT(",");

	}
	return Data;
}

void AANetBaseCharacter::ParseCustomizationData(FString BodyPartData)
{
	TArray<FString> ArrayData;
	BodyPartData.ParseIntoArray(ArrayData, TEXT(","));
	for (size_t i = 0; i < ArrayData.Num(); i++)
	{
		BodyPartIndices[i] = FCString::Atoi(*ArrayData[i]);
	}
}

void AANetBaseCharacter::ChangeBodyPart(EBodyPart index, int value, bool DirectSet)
{
	FSMeshAssetList* List = GetBodyPartList(index, BodyPartIndices[(int)EBodyPart::BP_BodyType] != 0);
	
	if (List == nullptr) return;

	int CurrentIndex = BodyPartIndices[(int)index];

	if (DirectSet)
	{
		CurrentIndex = value;
	}
	else
	{
		CurrentIndex += value;
	}

	int Num = List->ListSkeletal.Num() + List->ListStatic.Num();

	if (CurrentIndex < 0)
	{
		CurrentIndex += Num;
	}
	else
		CurrentIndex %= Num;

	BodyPartIndices[(int)index] = CurrentIndex;


	switch (index)
	{
	case EBodyPart::BP_Face:PartFace->SetSkeletalMeshAsset(List->ListSkeletal[CurrentIndex]); break;
	case EBodyPart::BP_Beard:PartBeard->SetStaticMesh(List->ListStatic[CurrentIndex]); break;
	case EBodyPart::BP_Chest:GetMesh()->SetSkeletalMeshAsset(List->ListSkeletal[CurrentIndex]); break;
	case EBodyPart::BP_Hair:PartHair->SetStaticMesh(List->ListStatic[CurrentIndex]); break;
	case EBodyPart::BP_Hands:PartHands->SetSkeletalMeshAsset(List->ListSkeletal[CurrentIndex]); break;
	case EBodyPart::BP_Legs:PartLegs->SetSkeletalMeshAsset(List->ListSkeletal[CurrentIndex]); break;
	case EBodyPart::BP_EyeBrows:PartEyeBrows->SetStaticMesh(List->ListStatic[CurrentIndex]); break;
	}
}

void AANetBaseCharacter::ChangeGender(bool _isFemale)
{
	
	UpdateBodyParts();
}

void AANetBaseCharacter::CheckPlayerState()
{
	ANetPlayerState* State = GetPlayerState<ANetPlayerState>();

	if (State == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("State == nullptr"));

		GWorld->GetTimerManager().SetTimer(ClientDataCheckTimer, this, &AANetBaseCharacter::CheckPlayerState, 0.25f, false);

	}
	else
	{
		if (IsLocallyControlled())
		{
			UNetGameInstance* Instance = Cast<UNetGameInstance>(GWorld->GetGameInstance());
			if (Instance)
			{
				SubmitPlayerInfoToServer(Instance->PlayerInfo);
			}
		}
		CheckPlayerInfo();
	}
}

void AANetBaseCharacter::CheckPlayerInfo()
{
	ANetPlayerState* State = GetPlayerState<ANetPlayerState>();

	if (State && PlayerInfoReceived)
	{
		ParseCustomizationData(State->Data.CustomizationData);
		UpdateBodyParts();
		OnPlayerInfoChanged();
		SetActorHiddenInGame(false);

	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("State Not Received!"));

		GWorld->GetTimerManager().SetTimer(ClientDataCheckTimer, this, &AANetBaseCharacter::CheckPlayerInfo, 0.25, false);

	}
}


void AANetBaseCharacter::SubmitPlayerInfoToServer_Implementation(FSPlayerInfo Info)
{
	ANetPlayerState* State = GetPlayerState<ANetPlayerState>();
	State->Data.Nickname = Info.Nickname;
	State->Data.CustomizationData = Info.CustomizationData;
	State->Data.TeamID = Info.TeamID;
	PlayerInfoReceived = true;
}


FSMeshAssetList* AANetBaseCharacter::GetBodyPartList(EBodyPart part, bool isFemale)
{
	FString Name = FString::Printf(TEXT("%s%s"), isFemale ? TEXT("Female") : TEXT("Male"), BodyPartNames[(int)part]);
	return SBodyParts ? SBodyParts->FindRow<FSMeshAssetList>(*Name, nullptr) : nullptr;
}


void AANetBaseCharacter::UpdateBodyParts()
{
	ChangeBodyPart(EBodyPart::BP_Face, 0, false);
	ChangeBodyPart(EBodyPart::BP_Beard, 0, false);
	ChangeBodyPart(EBodyPart::BP_Chest, 0, false);
	ChangeBodyPart(EBodyPart::BP_Hair, 0, false);
	ChangeBodyPart(EBodyPart::BP_Hands, 0, false);
	ChangeBodyPart(EBodyPart::BP_Legs, 0, false);
	ChangeBodyPart(EBodyPart::BP_EyeBrows, 0, false);
}



