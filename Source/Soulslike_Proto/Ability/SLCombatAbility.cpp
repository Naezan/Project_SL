// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability/SLCombatAbility.h"
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

void USLCombatAbility::TriggerAbility()
{
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
	OnEndAbilityDelegate.Clear();
}

bool USLCombatAbility::CanActivateAbility()
{
	ACharacter* AvatarActor = Cast<ACharacter>(GetOwningPawn());

	return AvatarActor ? AvatarActor->GetCharacterMovement()->IsMovingOnGround() : false;
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
