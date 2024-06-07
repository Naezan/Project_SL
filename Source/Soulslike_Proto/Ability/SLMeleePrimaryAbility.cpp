// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability/SLMeleePrimaryAbility.h"
#include "Character/CombatInterface.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"

void USLMeleePrimaryAbility::TriggerAbility()
{
	if (CanChangeComboSection())
	{
		MoveToNextComboSection();
		return;
	}

	if (IsMontagePlaying())
	{
		return;
	}

	Super::TriggerAbility();
}

void USLMeleePrimaryAbility::EndAbility()
{
	Super::EndAbility();

	ComboSectionInfo.ResetIndex();
}

bool USLMeleePrimaryAbility::IsOverlappingAbility()
{
	return true;
}

void USLMeleePrimaryAbility::OnNotifyBegin(FName NotifyName)
{
	if (AttackInfo.NotifyName.IsEqual(NotifyName))
	{
		FCollisionObjectQueryParams ObjectParams(ECC_Pawn);
		FCollisionQueryParams QueryParams(FName("SweepSingleAttack"), false, GetOwningPawn());

		FVector Start = GetOwningPawn()->GetActorLocation();
		FVector End = Start + GetOwningPawn()->GetActorForwardVector() * AttackInfo.DepthRange;

		FHitResult OutHit;
		GetWorld()->SweepSingleByObjectType(OutHit, Start, End, FQuat::Identity, ObjectParams, FCollisionShape::MakeSphere(AttackInfo.WidthRange), QueryParams);

		FVector const TraceVec = End - Start;
		float const Dist = TraceVec.Size();

		FVector const Center = Start + TraceVec * 0.5f;
		float const HalfHeight = (Dist * 0.5f) + AttackInfo.WidthRange;

		FQuat const CapsuleRot = FRotationMatrix::MakeFromZ(TraceVec).ToQuat();

		if (OutHit.bBlockingHit)
		{
			if (ICombatInterface* CombatInterface = Cast<ICombatInterface>(GetOwningPawn()))
			{
				CombatInterface->ApplyWeaponDamage(OutHit.GetActor(), nullptr);
			}

			DrawDebugCapsule(GetWorld(), Center, HalfHeight, AttackInfo.WidthRange, CapsuleRot, FColor::Red, false, 2.f);
		}
		else
		{
			DrawDebugCapsule(GetWorld(), Center, HalfHeight, AttackInfo.WidthRange, CapsuleRot, FColor::Green, false, 2.f);
		}
	}
}

bool USLMeleePrimaryAbility::CanChangeComboSection()
{
	if (UAnimInstance* AnimInstance = GetAvatarAnimInstance())
	{
		float ComboCurveValue = -1.f;
		AnimInstance->GetCurveValue(ComboSectionInfo.CurveName, ComboCurveValue);

		return ComboCurveValue > 0.1f;
	}
	
	return false;
}

void USLMeleePrimaryAbility::MoveToNextComboSection()
{
	if (UAnimInstance* AnimInstance = GetAvatarAnimInstance())
	{
		ComboSectionInfo.IncreatementSection();

		AnimInstance->Montage_JumpToSection(ComboSectionInfo.GetCurrentSectionName());
	}
}

void FComboSectionInfo::ResetIndex()
{
	CurrentSectionIndex = 0;
}

const FName FComboSectionInfo::GetCurrentSectionName()
{
	if (SectionNames.Num() > CurrentSectionIndex)
	{
		return SectionNames[CurrentSectionIndex];
	}

	return FName();
}

void FComboSectionInfo::IncreatementSection()
{
	++CurrentSectionIndex;

	CurrentSectionIndex = SectionNames.Num() > 0 ? FMath::Clamp(CurrentSectionIndex, 0, SectionNames.Num() - 1) : 0;
}
