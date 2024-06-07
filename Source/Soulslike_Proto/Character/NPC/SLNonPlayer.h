// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/SLCombatCharacter.h"
#include "SLNonPlayer.generated.h"

/**
 *
 */
UCLASS()
class SOULSLIKE_PROTO_API ASLNonPlayer : public ASLCombatCharacter
{
	GENERATED_BODY()

public:
	ASLNonPlayer();

protected:
	virtual void DeathStart() override;
	virtual void DeathEnd() override;
};
