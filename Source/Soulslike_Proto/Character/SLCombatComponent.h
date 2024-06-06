// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Component/PawnComponent.h"
#include "GameplayTagContainer.h"
#include "SLCombatComponent.generated.h"

class USLCombatAbility;

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
	void OnDeActivateAbility();
	void RegisterAbility(FGameplayTag AbilityTag, TSubclassOf<USLCombatAbility> CombatAbility);
	void UnRegisterAbility();

	void RegisterBlockTag(FGameplayTag InBlockTag);
	void RegisterBlockTags(TSet<FGameplayTag>& InBlockTags);
	void UnRegisterBlockTag(FGameplayTag InBlockTag);
	void UnRegisterBlockTags(TSet<FGameplayTag>& InBlockTags);
	bool HasBlockTag(FGameplayTag InBlockTag);
	bool HasBlockTags(TSet<FGameplayTag>& InBlockTags);

	bool HasActiveAbility() const { return bHasActiveAbility; }

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Ability, meta = (AllowPrivateAccess = "true"))
	TMap<FGameplayTag, USLCombatAbility*> GrantedAbilities;

	//해당 태그를 가지고 있는 스킬은 활성화될 수 없습니다.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Ability, meta = (AllowPrivateAccess = "true"))
	TSet<FGameplayTag> GrantedBlockTags;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Ability, meta = (AllowPrivateAccess = "true"))
	USLCombatAbility* ActivatedAbility;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Ability, meta = (AllowPrivateAccess = "true"))
	uint8 bHasActiveAbility : 1;
};
