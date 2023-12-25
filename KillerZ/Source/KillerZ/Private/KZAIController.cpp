// Fill out your copyright notice in the Description page of Project Settings.


#include "KZAIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTree.h"

AKZAIController::AKZAIController()
{
	BehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("Behavior Tree Component"));
	BlackboardComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("Blackboard Component"));
}

void AKZAIController::BeginPlay()
{
	Super::BeginPlay(); 

	if (IsValid(BehaviourTree.Get()))
	{
		RunBehaviorTree(BehaviourTree.Get());
		BehaviorTreeComponent->StartTree(*BehaviourTree.Get());
	}
}

void AKZAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (IsValid(Blackboard.Get()) && IsValid(BehaviourTree.Get()))
	{
		Blackboard->InitializeBlackboard(*BehaviourTree.Get()->BlackboardAsset.Get());
	}
}
