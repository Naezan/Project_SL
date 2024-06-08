// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Node/BTTask_RotateToTarget.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_RotateToTarget::UBTTask_RotateToTarget()
{
	NodeName = TEXT("RotateToTarget");
}

EBTNodeResult::Type UBTTask_RotateToTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	AAIController* OwnerController = OwnerComp.GetAIOwner();
	UObject* TargetObject = OwnerComp.GetBlackboardComponent()->
		GetValueAsObject(TargetKey.SelectedKeyName);

	APawn* ControlledPawn = OwnerController->GetPawn();
	AActor* Target = Cast<AActor>(TargetObject);

	if (OwnerController == nullptr || TargetObject == nullptr ||
		ControlledPawn == nullptr || Target == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	FVector LookVector = Target->GetActorLocation() - ControlledPawn->GetActorLocation();
	LookVector.Z = 0.0f;
	FRotator TargetRot = FRotationMatrix::MakeFromX(LookVector).Rotator();
	ControlledPawn->SetActorRotation(FMath::RInterpTo(ControlledPawn->GetActorRotation(), TargetRot, GetWorld()->GetDeltaSeconds(), RotateSpeed));

	return EBTNodeResult::Succeeded;
}