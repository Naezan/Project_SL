// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/SLCombatCharacter.h"
#include "Character/SLCombatComponent.h"
#include "Character/SLEquipmentComponent.h"
#include "Character/SLStatComponent.h"

ASLCombatCharacter::ASLCombatCharacter()
{
	CombatComponent = CreateDefaultSubobject<USLCombatComponent>(TEXT("CombatComponent"));
	EquipComponent = CreateDefaultSubobject<USLEquipmentComponent>(TEXT("EquipComponent"));
	StatComponent = CreateDefaultSubobject<USLStatComponent>(TEXT("StatComponent"));
}

void ASLCombatCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (EquipComponent != nullptr)
	{
		EquipComponent->EquipOnStart();
	}
}

float ASLCombatCharacter::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	return Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
}

void ASLCombatCharacter::OnAbilityTrigger(FGameplayTag TriggerTag)
{
	if (CombatComponent != nullptr)
	{
		CombatComponent->OnActivateAbility(TriggerTag);
	}
}

bool ASLCombatCharacter::HasActiveCombatAbility()
{
	if (CombatComponent != nullptr)
	{
		return CombatComponent->HasActiveAbility();
	}

	return false;
}

void ASLCombatCharacter::RegisterCombatAbility(FGameplayTag AbilityTag, TSubclassOf<USLCombatAbility> CombatAbility)
{
	if (CombatComponent != nullptr)
	{
		CombatComponent->RegisterAbility(AbilityTag, CombatAbility);
	}
}

void ASLCombatCharacter::UnRegisterCombatAbility()
{
	if (CombatComponent != nullptr)
	{
		CombatComponent->OnDeActivateAbility();
		CombatComponent->UnRegisterAbility();
	}
}

void ASLCombatCharacter::DeathStart()
{
	UnRegisterCombatAbility();

	if (EquipComponent != nullptr)
	{
		EquipComponent->UnEquip();
	}
}

void ASLCombatCharacter::DeathEnd()
{
}
