// Fill out your copyright notice in the Description page of Project Settings.


#include "Equipment/SLEquipmentComponent.h"
#include "Combat/CombatInterface.h"
#include "Weapon/SLWeaponActor.h"
#include "Weapon/SLWeaponDataAsset.h"

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

		CombatControl->RegisterWeaponAttribute(WeaponDataAsset->WeaponAttribute);
	}
}

void USLEquipmentComponent::UnEquip()
{
	if (EquippedWeapon)
	{
		EquippedWeapon->SetSimulatePhysicsOnWeapon(true);
		EquippedWeapon->SetWeaponCollisionPreset("BlockAll");
		EquippedWeapon->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);

		EquippedWeapon = nullptr;
	}

	if (ICombatInterface* CombatControl = Cast<ICombatInterface>(GetPawn()))
	{
		for (const auto& AbilityInfo : WeaponDataAsset->WeaponAbiliies)
		{
			CombatControl->UnRegisterCombatAbility(AbilityInfo.AbilityTag);
		}
		CombatControl->UnRegisterWeaponAttribute();
	}
}

bool USLEquipmentComponent::IsEquipped() const
{
	return (EquippedWeapon != nullptr);
}
