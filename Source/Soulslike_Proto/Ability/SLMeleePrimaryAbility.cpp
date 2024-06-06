// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability/SLMeleePrimaryAbility.h"

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
