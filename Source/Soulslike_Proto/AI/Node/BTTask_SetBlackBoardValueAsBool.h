// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_SetBlackBoardValueAsBool.generated.h"

/**
 * 
 */
UCLASS()
class SOULSLIKE_PROTO_API UBTTask_SetBlackBoardValueAsBool : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UBTTask_SetBlackBoardValueAsBool();

	virtual EBTNodeResult::Type ExecuteTask(
		UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
	UPROPERTY(EditAnywhere, Category = BlackBoard)
	FBlackboardKeySelector BlackboardKey;
	UPROPERTY(EditAnywhere, Category = BlackBoard)
	uint8 bIsTrue : 1;
};
