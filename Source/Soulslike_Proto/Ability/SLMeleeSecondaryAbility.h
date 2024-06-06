// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ability/SLCombatAbility.h"
#include "SLMeleeSecondaryAbility.generated.h"

/**
 * 
 */
UCLASS()
class SOULSLIKE_PROTO_API USLMeleeSecondaryAbility : public USLCombatAbility
{
	GENERATED_BODY()
	
public:
	virtual void TriggerAbility() override;
	virtual void EndAbility() override;

private:
	void SelectDirSection();
};
