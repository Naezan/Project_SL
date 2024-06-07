// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Node/BTTask_ClearFocusTarget.h"
#include "AIController.h"

UBTTask_ClearFocusTarget::UBTTask_ClearFocusTarget()
{
	NodeName = TEXT("ClearFocusTarget");
}

EBTNodeResult::Type UBTTask_ClearFocusTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	AAIController* OwnerController = OwnerComp.GetAIOwner();

	if (!OwnerController)
		return EBTNodeResult::Failed;

	OwnerController->ClearFocus(EAIFocusPriority::Gameplay);
	
	return EBTNodeResult::Succeeded;
}
