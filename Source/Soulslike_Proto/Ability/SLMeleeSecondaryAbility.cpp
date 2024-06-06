// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability/SLMeleeSecondaryAbility.h"

void USLMeleeSecondaryAbility::TriggerAbility()
{
	SelectDirSection();

	Super::TriggerAbility();
}

void USLMeleeSecondaryAbility::EndAbility()
{
	Super::EndAbility();

	//ResetDirectionInfo
}

void USLMeleeSecondaryAbility::SelectDirSection()
{
	
}
