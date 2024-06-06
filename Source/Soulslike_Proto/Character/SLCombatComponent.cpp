// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/SLCombatComponent.h"
#include "Ability/SLCombatAbility.h"

void USLCombatComponent::OnActivateAbility(FGameplayTag TriggerTag)
{
	// 현재 활성화중인 스킬이 있으면 중지, 단 콤보공격의 경우엔 넘어감
	if (bHasActiveAbility && (ActivatedAbility != nullptr && !ActivatedAbility->IsOverlappingAbility()))
	{
		return;
	}

	if (GrantedAbilities.Contains(TriggerTag))
	{
		if (GrantedAbilities[TriggerTag]->CanActivateAbility())
		{
			ActivatedAbility = GrantedAbilities[TriggerTag];

			ActivatedAbility->OnEndAbilityDelegate.Clear();
			ActivatedAbility->OnEndAbilityDelegate.BindDynamic(this, &ThisClass::OnDeActivateAbility);

			ActivatedAbility->TriggerAbility();

			bHasActiveAbility = true;
		}
	}
}

void USLCombatComponent::OnDeActivateAbility()
{
	if (ActivatedAbility != nullptr)
	{
		ActivatedAbility->EndAbility();

		ActivatedAbility = nullptr;
		bHasActiveAbility = false;
	}
}

void USLCombatComponent::RegisterAbility()
{
	for (const auto& AbilityInfo : CombatAbilities)
	{
		if (!GrantedAbilities.Contains(AbilityInfo.AbilityTag))
		{
			USLCombatAbility* CombatAbility = NewObject<USLCombatAbility>(GetPawn(), AbilityInfo.Ability);
			CombatAbility->Initialize(this);

			GrantedAbilities.Emplace(AbilityInfo.AbilityTag, CombatAbility);
		}
	}
}

void USLCombatComponent::UnRegisterAbility()
{
	if (!GrantedAbilities.IsEmpty())
	{
		GrantedAbilities.Empty();
	}
}

void USLCombatComponent::RegisterBlockTag(FGameplayTag InBlockTag)
{
	if (!GrantedBlockTags.Contains(InBlockTag))
	{
		GrantedBlockTags.Emplace(InBlockTag);
	}
}

void USLCombatComponent::RegisterBlockTags(TSet<FGameplayTag>& InBlockTags)
{
	if (InBlockTags.IsEmpty())
	{
		return;
	}

	for (const auto& Tag : InBlockTags)
	{
		if (!GrantedBlockTags.Contains(Tag))
		{
			GrantedBlockTags.Emplace(Tag);
		}
	}
}

void USLCombatComponent::UnRegisterBlockTag(FGameplayTag InBlockTag)
{
	GrantedBlockTags.Remove(InBlockTag);
}

void USLCombatComponent::UnRegisterBlockTags(TSet<FGameplayTag>& InBlockTags)
{
	if (InBlockTags.IsEmpty())
	{
		return;
	}

	for (const auto& Tag : InBlockTags)
	{
		GrantedBlockTags.Remove(Tag);
	}
}

bool USLCombatComponent::HasBlockTag(FGameplayTag InBlockTag)
{
	return GrantedBlockTags.Contains(InBlockTag);
}

bool USLCombatComponent::HasBlockTags(TSet<FGameplayTag>& InBlockTags)
{
	if (InBlockTags.IsEmpty())
	{
		return false;
	}

	for (const auto& Tag : InBlockTags)
	{
		if (GrantedBlockTags.Contains(Tag))
		{
			return true;
		}
	}

	return false;
}
