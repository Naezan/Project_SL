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
class UDamageType;

struct FWeaponAttributeInfo;

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

public:
	/* IAbilityControlInterface */
	virtual void OnAbilityTrigger(FGameplayTag TriggerTag) override;
	/* ~IAbilityControlInterface */

	/* ICombatInterface */
	virtual bool HasActiveCombatAbility() override;
	virtual void RegisterCombatAbility(FGameplayTag AbilityTag, TSubclassOf<USLCombatAbility> CombatAbility) override;
	virtual void UnRegisterCombatAbility(FGameplayTag AbilityTag) override;

	virtual void RegisterWeaponAttribute(FWeaponAttributeInfo WeaponAttribute) override;
	virtual void UnRegisterWeaponAttribute() override;

	virtual void ApplyWeaponDamage(AActor* DamageVictim, TSubclassOf<UDamageType> DamageTypeClass) override;

	virtual void DeathStart() override;
	virtual void DeathEnd() override;
	/* ~ICombatInterface */

	void RagDoll();

protected:
	virtual float TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

private:
	void InitHpBarWidget();

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component|Combat", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USLCombatComponent> CombatComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component|Equipment", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USLEquipmentComponent> EquipComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component|Stat", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USLStatComponent> StatComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Widget", Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UWidgetComponent> HpWidget;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Widget", Meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UUserWidget> HpWidgetClass;
};
