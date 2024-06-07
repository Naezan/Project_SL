// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Component/PawnComponent.h"
#include "SLStatComponent.generated.h"

/**
 * 
 */
UCLASS()
class SOULSLIKE_PROTO_API USLStatComponent : public UPawnComponent
{
	GENERATED_BODY()

public:
	USLStatComponent();

public:
	float GetMaxHealth() const { return MaxHealth; }
	float GetHealth() const { return Health; }
	float GetMaxStamina() const { return MaxStamina; }
	float GetStamina() const { return Stamina; }
	float GetAttackDamage() const { return AttackDamage; }

	void InitAttribute();
	void InitAttackDamage(float InAttackDamage);
	void AddAttackDamage(float InAttackDamage);
	void ResetAttribute();

	// 데미지 만큼 체력 감소
	float ApplyAttackDamage(float InDamage);
	
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat, meta = (AllowPrivateAccess = "true"))
	float MaxHealth;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stat, meta = (AllowPrivateAccess = "true"))
	float Health;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat, meta = (AllowPrivateAccess = "true"))
	float MaxStamina;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stat, meta = (AllowPrivateAccess = "true"))
	float Stamina;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stat, meta = (AllowPrivateAccess = "true"))
	float AttackDamage;
};
