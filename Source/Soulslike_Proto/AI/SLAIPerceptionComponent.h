// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AIPerceptionTypes.h"
#include "SLAIPerceptionComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPerceptionStimulusExired, const FAIStimulus&, Stimulus);

/**
 * 
 */
UCLASS()
class SOULSLIKE_PROTO_API USLAIPerceptionComponent : public UAIPerceptionComponent
{
	GENERATED_BODY()
	
public:
	USLAIPerceptionComponent();

protected:
	virtual void HandleExpiredStimulus(FAIStimulus& StimulusStore) override;

public:
	FPerceptionStimulusExired OnStimuliExpired;
};
