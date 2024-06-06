// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/SLCombatComponent.h"
#include "Ability/SLCombatAbility.h"

void USLCombatComponent::OnActivateAbility(FGameplayTag TriggerTag)
{
	// ���� Ȱ��ȭ���� ��ų�� ������ ����, �� �޺������� ��쿣 �Ѿ
	if (bHasActiveAbility && (ActivatedAbility != nullptr && !ActivatedAbility->IsOverlappingAbility()))
	{
		return;
	}

	if (GrantedAbilities.Contains(TriggerTag))
	{
		ActivatedAbility = GrantedAbilities[TriggerTag];

		ActivatedAbility->OnEndAbilityDelegate.Clear();
		ActivatedAbility->OnEndAbilityDelegate.BindDynamic(this, &ThisClass::OnDeActivateAbility);

		if (ActivatedAbility != nullptr && ActivatedAbility->CanActivateAbility())
		{
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
			GrantedAbilities.Emplace(AbilityInfo.AbilityTag, NewObject<USLCombatAbility>(GetPawn(), AbilityInfo.Ability));
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
