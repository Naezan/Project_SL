// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SLWeaponActor.generated.h"

UCLASS()
class SOULSLIKE_PROTO_API ASLWeaponActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ASLWeaponActor();

	void SetSimulatePhysicsOnWeapon(bool bSimulate);
	void SetWeaponCollisionPreset(FName ProfileName);

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* WeaponMeshComponent;
};
