// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/SLCombatComponent.h"
#include "Ability/SLCombatAbility.h"

void USLCombatComponent::OnActivateAbility(FGameplayTag TriggerTag)
{
	// 현재 활성화중인 스킬이 있으면 스킵, 단 콤보공격의 경우엔 넘어감
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
			ActivatedAbility->OnEndAbilityDelegate.BindDynamic(this, &ThisClass::OnEndAbility);

			ActivatedAbility->TriggerAbility();

			bHasActiveAbility = true;
		}
	}
}

void USLCombatComponent::OnEndAbility()
{
	if (ActivatedAbility != nullptr)
	{
		ActivatedAbility->OnEndAbilityDelegate.Clear();
		ActivatedAbility->EndAbility();

		ActivatedAbility = nullptr;
		bHasActiveAbility = false;
	}
}

void USLCombatComponent::RegisterAbility(FGameplayTag AbilityTag, TSubclassOf<USLCombatAbility> CombatAbility)
{
	if (!GrantedAbilities.Contains(AbilityTag))
	{
		USLCombatAbility* NewAbility = NewObject<USLCombatAbility>(GetPawn(), CombatAbility);
		NewAbility->Initialize(this);

		GrantedAbilities.Emplace(AbilityTag, NewAbility);
	}
}

void USLCombatComponent::RegisterDefualtAbilities()
{
	for (const auto& Info : DefaultAbilities)
	{
		if (!GrantedBlockTags.Contains(Info.AbilityTag))
		{
			USLCombatAbility* NewAbility = NewObject<USLCombatAbility>(GetPawn(), Info.Ability);
			NewAbility->Initialize(this);

			GrantedAbilities.Emplace(Info.AbilityTag, NewAbility);
		}
	}
}

void USLCombatComponent::UnRegisterAbility(FGameplayTag AbilityTag)
{
	if (GrantedBlockTags.Contains(AbilityTag))
	{
		GrantedAbilities.Remove(AbilityTag);
	}
}

void USLCombatComponent::UnRegisterAllAbilities()
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

void USLCombatComponent::DeathStart()
{
	if (ActivatedAbility)
	{
		ActivatedAbility->StopMontage();
	}

	OnEndAbility();

	OnActivateAbility(DeathTag);
}

void USLCombatComponent::PlayHitMontage(AActor* Attacker)
{
	FVector AttackerDirection = (Attacker->GetActorLocation() - GetPawn()->GetActorLocation()).GetSafeNormal();

	FVector ForwardVector = GetPawn()->GetActorForwardVector();
	FVector RightVector = GetPawn()->GetActorRightVector();

	float ForwardDot = FVector::DotProduct(AttackerDirection, ForwardVector);
	float RightDot = FVector::DotProduct(AttackerDirection, RightVector);

	if (FMath::Abs(ForwardDot) > FMath::Abs(RightDot))
	{
		DamageDirection = ForwardDot > 0.707 ? EDamageDirection::Forward : EDamageDirection::Backward;
	}
	else
	{
		DamageDirection = RightDot > 0.707 ? EDamageDirection::Right : EDamageDirection::Left;
	}

	if (HitReactMontageMap.Contains(DamageDirection))
	{
		HitReactMontage = HitReactMontageMap[DamageDirection];
	}

	if (HitReactMontage)
	{
		GetPawnMeshComponent()->GetAnimInstance()->Montage_Play(HitReactMontage);
	}
}
