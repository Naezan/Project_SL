// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ability/SLCombatAbility.h"
#include "SLDeathAbility.generated.h"

/**
 * 
 */
UCLASS()
class SOULSLIKE_PROTO_API USLDeathAbility : public USLCombatAbility
{
	GENERATED_BODY()
	
public:
	virtual void TriggerAbility() override;
	virtual void EndAbility() override;

protected:
	virtual void OnNotifyBegin(FName NotifyName) override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Death|Notify", meta = (AllowPrivateAccess = "true"))
	FName DeathNotifyName;
};
