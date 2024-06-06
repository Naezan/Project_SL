// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Component/PawnComponent.h"
#include "SLEquipmentComponent.generated.h"

class USLWeaponDataAsset;
class ASLWeaponActor;

/**
 * 
 */
UCLASS()
class SOULSLIKE_PROTO_API USLEquipmentComponent : public UPawnComponent
{
	GENERATED_BODY()
	
public:
	void EquipOnStart();
	void Equip();
	void UnEquip();

	bool IsEquipped() const;

private:
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USLWeaponDataAsset> WeaponDataAsset;

	UPROPERTY()
	TObjectPtr<ASLWeaponActor> EquippedWeapon;
};
