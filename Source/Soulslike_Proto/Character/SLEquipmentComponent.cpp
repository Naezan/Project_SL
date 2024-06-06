// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/SLEquipmentComponent.h"
#include "Weapon/SLWeaponDataAsset.h"
#include "Weapon/SLWeaponActor.h"
#include "Character/CombatInterface.h"

void USLEquipmentComponent::EquipOnStart()
{
	Equip();
}

void USLEquipmentComponent::Equip()
{
	if (USkeletalMeshComponent* SKMC = GetPawnMeshComponent())
	{
		EquippedWeapon = GetWorld()->SpawnActorDeferred<ASLWeaponActor>(WeaponDataAsset->WeaponMeshActor, FTransform::Identity, GetPawn());

		// if you don't AttachToActor is null
		EquippedWeapon->FinishSpawning(FTransform::Identity, true);
		EquippedWeapon->AttachToComponent(SKMC, FAttachmentTransformRules::SnapToTargetNotIncludingScale, WeaponDataAsset->WeaponSocket);

		EquippedWeapon->SetWeaponCollisionPreset("NoCollision");
	}

	if (ICombatInterface* CombatControl = Cast<ICombatInterface>(GetPawn()))
	{
		for (const auto& AbilityInfo : WeaponDataAsset->WeaponAbiliies)
		{
			CombatControl->RegisterCombatAbility(AbilityInfo.AbilityTag, AbilityInfo.Ability);
		}
	}
}

void USLEquipmentComponent::UnEquip()
{
	if (EquippedWeapon)
	{
		EquippedWeapon->SetSimulatePhysicsOnWeapon(true);
		EquippedWeapon->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);

		EquippedWeapon->SetWeaponCollisionPreset("BlockAll");
	}

	if (ICombatInterface* CombatControl = Cast<ICombatInterface>(GetPawn()))
	{
		CombatControl->UnRegisterCombatAbility();
	}
}

bool USLEquipmentComponent::IsEquipped() const
{
	return (EquippedWeapon != nullptr);
}
