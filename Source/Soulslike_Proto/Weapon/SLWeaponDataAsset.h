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

/**
 * 
 */
UCLASS()
class SOULSLIKE_PROTO_API USLWeaponDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	USLWeaponDataAsset();

	UPROPERTY(EditDefaultsOnly)
	FName WeaponSocket;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ASLWeaponActor> WeaponMeshActor;

	UPROPERTY(EditDefaultsOnly)
	TArray<FAbilityInfo> WeaponAbiliies;
};
