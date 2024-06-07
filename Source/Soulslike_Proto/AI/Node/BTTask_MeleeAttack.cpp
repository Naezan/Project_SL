// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Node/BTTask_MeleeAttack.h"
#include "AIController.h"

UBTTask_MeleeAttack::UBTTask_MeleeAttack()
{
	NodeName = TEXT("MeleeAttack");
}

EBTNodeResult::Type UBTTask_MeleeAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	AAIController* OwnerController = OwnerComp.GetAIOwner();
	OwnerController->GetPawn();

	if (!OwnerController)
		return EBTNodeResult::Failed;

	//TODO ÄÞº¸°ø°Ý

	return EBTNodeResult::Succeeded;
}
