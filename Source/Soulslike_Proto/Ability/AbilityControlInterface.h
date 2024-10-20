// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "UObject/Interface.h"
#include "AbilityControlInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UAbilityControlInterface : public UInterface
{
	GENERATED_BODY()
};

DECLARE_DELEGATE(FOnAbilityEndDelegate);

class SOULSLIKE_PROTO_API IAbilityControlInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void OnAbilityTrigger(FGameplayTag TriggerTag) {}
	virtual void SetAbilityEndDelegate(const FOnAbilityEndDelegate& InAbilityEndDelegate) {}
	virtual void ExecuteOnAbilityEndDelegate() {}
};
