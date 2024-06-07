// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/SLStatComponent.h"

USLStatComponent::USLStatComponent()
{
	
}

void USLStatComponent::InitAttribute()
{
	Health = MaxHealth;
	Stamina = MaxStamina;
}

void USLStatComponent::InitAttackDamage(float InAttackDamage)
{
	AttackDamage = InAttackDamage;
}

void USLStatComponent::AddAttackDamage(float InAttackDamage)
{
	AttackDamage += InAttackDamage;
}

void USLStatComponent::ResetAttribute()
{
	Health = MaxHealth;
	Stamina = MaxStamina;

	AttackDamage = 0.f;
}

float USLStatComponent::ApplyAttackDamage(float InDamage)
{
	Health = FMath::Clamp(Health - InDamage, 0.f, MaxHealth);

	return Health;
}
