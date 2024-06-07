// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Node/BTTask_SetFocusTarget.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_SetFocusTarget::UBTTask_SetFocusTarget()
{
	NodeName = TEXT("SetFocusTarget");
}

EBTNodeResult::Type UBTTask_SetFocusTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	AAIController* OwnerController = OwnerComp.GetAIOwner();
	UObject* TargetObject =	OwnerComp.GetBlackboardComponent()->
		GetValueAsObject(TargetKey.SelectedKeyName);

	if (OwnerController == nullptr || TargetObject == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	if (AActor* Target = Cast<AActor>(TargetObject))
	{
		OwnerController->SetFocus(Target, EAIFocusPriority::Gameplay);
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}
