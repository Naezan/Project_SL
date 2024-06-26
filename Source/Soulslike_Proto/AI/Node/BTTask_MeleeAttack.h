// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_MeleeAttack.generated.h"

/**
 * 
 */
UCLASS()
class SOULSLIKE_PROTO_API UBTTask_MeleeAttack : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTask_MeleeAttack();

	virtual EBTNodeResult::Type ExecuteTask(
		UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

private:
	void OnFinishTack();

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attack|Tag", meta = (AllowPrivateAccess = "true"))
	FGameplayTag AttackTag;

	UPROPERTY()
	TObjectPtr<UBehaviorTreeComponent> MyOwnerComp;
};
