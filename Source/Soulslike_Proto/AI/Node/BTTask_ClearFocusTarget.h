// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_ClearFocusTarget.generated.h"

/**
 * 
 */
UCLASS()
class SOULSLIKE_PROTO_API UBTTask_ClearFocusTarget : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UBTTask_ClearFocusTarget();

	virtual EBTNodeResult::Type ExecuteTask(
		UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
