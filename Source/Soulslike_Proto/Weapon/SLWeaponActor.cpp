// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/SLWeaponActor.h"

// Sets default values
ASLWeaponActor::ASLWeaponActor()
{
	WeaponMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponMesh"));
	RootComponent = WeaponMeshComponent;
}

void ASLWeaponActor::SetSimulatePhysicsOnWeapon(bool bSimulate)
{
	WeaponMeshComponent->SetSimulatePhysics(bSimulate);
}

void ASLWeaponActor::SetWeaponCollisionPreset(FName ProfileName)
{
	WeaponMeshComponent->SetCollisionProfileName(ProfileName);
}
