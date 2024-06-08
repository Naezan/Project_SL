// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Node/BTTask_MeleeAttack.h"
#include "AIController.h"
#include "Ability/AbilityControlInterface.h"

UBTTask_MeleeAttack::UBTTask_MeleeAttack()
{
	NodeName = TEXT("MeleeAttack");
}

EBTNodeResult::Type UBTTask_MeleeAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	MyOwnerComp = &OwnerComp;

	AAIController* OwnerController = OwnerComp.GetAIOwner();
	IAbilityControlInterface* AbilityPawn = Cast<IAbilityControlInterface>(OwnerController->GetPawn());

	if (!OwnerController || !AbilityPawn)
		return EBTNodeResult::Failed;

	FOnAbilityEndDelegate OnAbilityEndDelegate;
	OnAbilityEndDelegate.BindUObject(this, &UBTTask_MeleeAttack::OnFinishTack);

	AbilityPawn->SetAbilityEndDelegate(OnAbilityEndDelegate);
	AbilityPawn->OnAbilityTrigger(AttackTag);

	return EBTNodeResult::InProgress;
}

void UBTTask_MeleeAttack::OnFinishTack()
{
	if (MyOwnerComp)
	{
		FinishLatentTask(*MyOwnerComp, EBTNodeResult::Succeeded);
	}
}
