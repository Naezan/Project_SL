// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability/SLCombatAbility.h"
#include "Character/SLCombatComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

APawn* USLCombatAbility::GetOwningPawn() const
{
	return Cast<APawn>(GetOuter());
}

USkeletalMeshComponent* USLCombatAbility::GetAvatarMeshComponent() const
{
	APawn* AvatarPawn = GetOwningPawn();

	return AvatarPawn ? AvatarPawn->FindComponentByClass<USkeletalMeshComponent>() : nullptr;
}

UAnimInstance* USLCombatAbility::GetAvatarAnimInstance() const
{
	USkeletalMeshComponent* AvatarMesh = GetAvatarMeshComponent();

	return AvatarMesh ? AvatarMesh->GetAnimInstance() : nullptr;
}

void USLCombatAbility::Initialize(UObject* InOwner)
{
	OwningCombatComponent = Cast<USLCombatComponent>(InOwner);
}

void USLCombatAbility::TriggerAbility()
{
	check(OwningCombatComponent);
	OwningCombatComponent->RegisterBlockTags(BlockAbilityTags);

	if (UAnimInstance* AnimInstance = GetAvatarAnimInstance())
	{
		float Duration = AnimInstance->Montage_Play(CombatMontage);

		if (Duration > 0.f)
		{
			if (OnCombatMontageEndDelegate.IsBound())
			{
				OnCombatMontageEndDelegate.Unbind();
			}

			OnCombatMontageEndDelegate.BindUObject(this, &ThisClass::OnEndMontage);
			AnimInstance->Montage_SetEndDelegate(OnCombatMontageEndDelegate, CombatMontage);
		}
		else
		{
			OnEndAbilityDelegate.ExecuteIfBound();
		}
	}
}

void USLCombatAbility::EndAbility()
{
	check(OwningCombatComponent);
	OwningCombatComponent->UnRegisterBlockTags(BlockAbilityTags);

	//GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString("OnEndAbility"));

	OnEndAbilityDelegate.Clear();
}

bool USLCombatAbility::CanActivateAbility()
{
	check(OwningCombatComponent);

	if (ACharacter* AvatarActor = Cast<ACharacter>(GetOwningPawn()))
	{
		return AvatarActor->GetCharacterMovement()->IsMovingOnGround() && !OwningCombatComponent->HasBlockTag(AbilityTag);
	}

	return false;
}

bool USLCombatAbility::IsOverlappingAbility()
{
	return false;
}

void USLCombatAbility::OnEndMontage(UAnimMontage* InMontage, bool bInterrupted)
{
	OnEndAbilityDelegate.ExecuteIfBound();
}

bool USLCombatAbility::IsMontagePlaying()
{
	if (UAnimInstance* AnimInstance = GetAvatarAnimInstance())
	{
		return AnimInstance->Montage_IsPlaying(CombatMontage);
	}

	return false;
}
