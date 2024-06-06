// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/SLCharacterBase.h"
#include "Ability/AbilityControlInterface.h"
#include "Character/CombatInterface.h"
#include "SLCombatCharacter.generated.h"

class USLCombatComponent;
class USLEquipmentComponent;
class USLStatComponent;

/**
 * 
 */
UCLASS()
class SOULSLIKE_PROTO_API ASLCombatCharacter : public ASLCharacterBase, public IAbilityControlInterface, public ICombatInterface
{
	GENERATED_BODY()
	
public:
	ASLCombatCharacter();

protected:
	virtual void BeginPlay() override;
	virtual float TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

public:
	/* IAbilityControlInterface */
	virtual void OnAbilityTrigger(FGameplayTag TriggerTag) override;

	/* ICombatInterface */
	virtual bool HasActiveCombatAbility() override;
	virtual void RegisterCombatAbility(FGameplayTag AbilityTag, TSubclassOf<USLCombatAbility> CombatAbility) override;
	virtual void UnRegisterCombatAbility() override;
	virtual void Death() override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component|Combat", meta = (AllowPrivateAccess = "true"))
	USLCombatComponent* CombatComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component|Equipment", meta = (AllowPrivateAccess = "true"))
	USLEquipmentComponent* EquipComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component|Stat", meta = (AllowPrivateAccess = "true"))
	USLStatComponent* StatComponent;
};
