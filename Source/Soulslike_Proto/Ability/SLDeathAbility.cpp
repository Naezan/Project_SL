// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability/SLDeathAbility.h"
#include "Character/CombatInterface.h"

void USLDeathAbility::TriggerAbility()
{
	Super::TriggerAbility();
}

void USLDeathAbility::EndAbility()
{
	Super::EndAbility();
}

void USLDeathAbility::OnNotifyBegin(FName NotifyName)
{
	if (DeathNotifyName.IsEqual(NotifyName))
	{
		if (ICombatInterface* CombatInterface = Cast<ICombatInterface>(GetOwningPawn()))
		{
			CombatInterface->DeathEnd();
		}
	}
}
