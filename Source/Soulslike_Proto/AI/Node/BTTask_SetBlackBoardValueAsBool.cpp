// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Node/BTTask_SetBlackBoardValueAsBool.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_SetBlackBoardValueAsBool::UBTTask_SetBlackBoardValueAsBool()
{
	NodeName = TEXT("SetBlackBoardValueAsBool");
}

EBTNodeResult::Type UBTTask_SetBlackBoardValueAsBool::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	AAIController* OwnerController = OwnerComp.GetAIOwner();

	if (OwnerController == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	OwnerComp.GetBlackboardComponent()->
		SetValueAsBool(BlackboardKey.SelectedKeyName, bIsTrue);

	return EBTNodeResult::Succeeded;
}
