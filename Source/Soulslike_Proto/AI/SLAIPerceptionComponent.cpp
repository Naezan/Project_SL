// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/SLAIPerceptionComponent.h"

USLAIPerceptionComponent::USLAIPerceptionComponent()
{
}

void USLAIPerceptionComponent::HandleExpiredStimulus(FAIStimulus& StimulusStore)
{
	OnStimuliExpired.Broadcast(StimulusStore);
}
