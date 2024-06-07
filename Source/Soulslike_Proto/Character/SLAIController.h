// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "SLAIController.generated.h"

class UBehaviorTree;
class USLAIPerceptionComponent;
struct FAIStimulus;

/**
 * 
 */
UCLASS()
class SOULSLIKE_PROTO_API ASLAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	ASLAIController();

	virtual void OnPossess(APawn* InPawn) override;

protected:
	UFUNCTION()
	void OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);

	UFUNCTION()
	void OnStimuliExpired(const FAIStimulus& Stimulus);

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI", Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UBehaviorTree> BTAsset;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI", Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USLAIPerceptionComponent> AIPerceptionComponent;
};
