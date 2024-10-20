// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Component/PawnComponent.h"
#include "GameplayTagContainer.h"
#include "Weapon/SLWeaponDataAsset.h"
#include "SLCombatComponent.generated.h"

class USLCombatAbility;

UENUM(BlueprintType)
enum class EDamageDirection : uint8
{
	None UMETA(DisplayName = "None"),
	Forward UMETA(DisplayName = "Forward"),
	Backward UMETA(DisplayName = "Backward"),
	Left UMETA(DisplayName = "Left"),
	Right UMETA(DisplayName = "Right")
};

/**
 * 
 */
UCLASS()
class SOULSLIKE_PROTO_API USLCombatComponent : public UPawnComponent
{
	GENERATED_BODY()

public:
	UFUNCTION()
	void OnActivateAbility(FGameplayTag TriggerTag);
	UFUNCTION()
	void OnEndAbility();
	void RegisterAbility(FGameplayTag AbilityTag, TSubclassOf<USLCombatAbility> CombatAbility);
	void RegisterDefualtAbilities();
	void UnRegisterAbility(FGameplayTag AbilityTag);
	void UnRegisterAllAbilities();

	void RegisterBlockTag(FGameplayTag InBlockTag);
	void RegisterBlockTags(TSet<FGameplayTag>& InBlockTags);
	void UnRegisterBlockTag(FGameplayTag InBlockTag);
	void UnRegisterBlockTags(TSet<FGameplayTag>& InBlockTags);
	bool HasBlockTag(FGameplayTag InBlockTag);
	bool HasBlockTags(TSet<FGameplayTag>& InBlockTags);

	bool HasActiveAbility() const { return bHasActiveAbility; }

	void DeathStart();
	void PlayHitMontage(AActor* Attacker);

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Ability, meta = (AllowPrivateAccess = "true"))
	TMap<FGameplayTag, USLCombatAbility*> GrantedAbilities;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Ability, meta = (AllowPrivateAccess = "true"))
	TArray<FAbilityInfo> DefaultAbilities;

	//해당 태그를 가지고 있는 스킬은 활성화될 수 없습니다.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Ability, meta = (AllowPrivateAccess = "true"))
	TSet<FGameplayTag> GrantedBlockTags;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Ability, meta = (AllowPrivateAccess = "true"))
	USLCombatAbility* ActivatedAbility;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Ability, meta = (AllowPrivateAccess = "true"))
	uint8 bHasActiveAbility : 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Ability, meta = (AllowPrivateAccess = "true"))
	FGameplayTag DeathTag;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = HitReact, meta = (AllowPrivateAccess = "true"))
	TMap<EDamageDirection, UAnimMontage*> HitReactMontageMap;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = HitReact, meta = (AllowPrivateAccess = "true"))
	EDamageDirection DamageDirection;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = HitReact, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UAnimMontage> HitReactMontage;
};
