// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTD_IsNearbyPlayer.generated.h"

/**
 * 
 */
UCLASS()
class SOULSLIKE_PROTO_API UBTD_IsNearbyPlayer : public UBTDecorator
{
	GENERATED_BODY()
	
public:
	UBTD_IsNearbyPlayer();

	virtual bool CalculateRawConditionValue(
		UBehaviorTreeComponent& OwnerComp,
		uint8* NodeMemory) const override;

protected:
	UPROPERTY(EditAnywhere, Category = BlackBoard)
	FBlackboardKeySelector TargetKey;
	UPROPERTY(EditAnywhere, Category = BlackBoard)
	float Distance;
};
