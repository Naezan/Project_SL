// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"
#include "SLWeaponDataAsset.generated.h"

class ASLWeaponActor;
class USLCombatAbility;

USTRUCT(BlueprintType)
struct FAbilityInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	FGameplayTag AbilityTag;

	UPROPERTY(EditAnywhere)
	TSubclassOf<USLCombatAbility> Ability;
};

USTRUCT(BlueprintType)
struct FWeaponAttributeInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	float Damage;
};

/**
 * 
 */
UCLASS()
class SOULSLIKE_PROTO_API USLWeaponDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	USLWeaponDataAsset();

	UPROPERTY(EditDefaultsOnly, Category = "Equipment")
	FName WeaponSocket;

	UPROPERTY(EditDefaultsOnly, Category = "Equipment")
	TSubclassOf<ASLWeaponActor> WeaponMeshActor;

	UPROPERTY(EditDefaultsOnly, Category = "Ability")
	TArray<FAbilityInfo> WeaponAbiliies;

	UPROPERTY(EditDefaultsOnly, Category = "Attribute")
	FWeaponAttributeInfo WeaponAttribute;
};
