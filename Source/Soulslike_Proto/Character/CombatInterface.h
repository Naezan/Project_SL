// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "GameplayTagContainer.h"
#include "Weapon/SLWeaponDataAsset.h"
#include "CombatInterface.generated.h"

class USLCombatAbility;
class UDamageType;

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UCombatInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class SOULSLIKE_PROTO_API ICombatInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	/* Ability */
	virtual bool HasActiveCombatAbility() { return false; }
	virtual void RegisterCombatAbility(FGameplayTag AbilityTag, TSubclassOf<USLCombatAbility> CombatAbility) {}
	virtual void UnRegisterCombatAbility(FGameplayTag AbilityTag) {}

	/* Attribute */
	virtual void RegisterWeaponAttribute(FWeaponAttributeInfo WeaponAttribute) {}
	virtual void UnRegisterWeaponAttribute() {}

	/* Damage */
	virtual void ApplyWeaponDamage(AActor* DamageVictim, TSubclassOf<UDamageType> DamageTypeClass) {}

	/* Death */
	virtual void DeathStart() {}
	virtual void DeathEnd() {}
};
