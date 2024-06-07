// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Node/BTD_IsNearbyPlayer.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTD_IsNearbyPlayer::UBTD_IsNearbyPlayer()
{
	NodeName = TEXT("IsNearbyPlayer");
}

bool UBTD_IsNearbyPlayer::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	bool bResult = Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

	AAIController* OwnerController = OwnerComp.GetAIOwner();
	UObject* TargetObject = OwnerComp.GetBlackboardComponent()->
		GetValueAsObject(TargetKey.SelectedKeyName);

	APawn* ControlledPawn = OwnerController->GetPawn();
	AActor* Target = Cast<AActor>(TargetObject);

	if (OwnerController == nullptr || TargetObject == nullptr ||
		ControlledPawn == nullptr || Target == nullptr)
	{
		return false;
	}

	float Dist = FVector::Distance(ControlledPawn->GetActorLocation(), Target->GetActorLocation());

	bResult = Dist <= Distance;

	return bResult;
}
