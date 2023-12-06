// Fill out your copyright notice in the Description page of Project Settings.


#include "ANetBaseCharacter.h"

static UDataTable* SBodyParts = nullptr;

static wchar_t* BodyPartNames[] =
{
	TEXT("Face"),
	TEXT("Hair"),
	TEXT("Chest"),
	TEXT("Hands"),
	TEXT("Legs"),
	TEXT("Beard")
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
	
}

void AANetBaseCharacter::OnConstruction(const FTransform& Transform)
{
}

// Called every frame
void AANetBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AANetBaseCharacter::ChangeBodyPart(EBodyPart index, int value, bool DirectSet)
{
}

void AANetBaseCharacter::ChangeGender(bool isFemale)
{
}

FSMeshAssetList* AANetBaseCharacter::GetBodyPartList(EBodyPart part, bool isFemale)
{
	return nullptr;
}

void AANetBaseCharacter::UpdateBodyParts()
{
}

// Called to bind functionality to input


