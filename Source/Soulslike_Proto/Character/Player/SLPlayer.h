// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/SLCharacterBase.h"
#include "Ability/AbilityControlInterface.h"
#include "Character/CombatInterface.h"
#include "SLPlayer.generated.h"

class USpringArmComponent;
class UCameraComponent;
class USLInputComponent;
class USLCombatComponent;
class USLEquipmentComponent;
class USLStatComponent;

class USLCombatAbility;

/**
 *
 */
UCLASS()
class SOULSLIKE_PROTO_API ASLPlayer : public ASLCharacterBase, public IAbilityControlInterface, public ICombatInterface
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component|Input", meta = (AllowPrivateAccess = "true"))
	USLInputComponent* ExtInputComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component|Combat", meta = (AllowPrivateAccess = "true"))
	USLCombatComponent* CombatComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component|Equipment", meta = (AllowPrivateAccess = "true"))
	USLEquipmentComponent* EquipComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component|Stat", meta = (AllowPrivateAccess = "true"))
	USLStatComponent* StatComponent;

public:
	ASLPlayer();

protected:
	virtual void SetupPlayerInputComponent(class UInputComponent* InPlayerInputComponent) override;
	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;
	virtual void BeginDestroy() override;
	virtual float TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;


public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

public:
	/* IAbilityControlInterface */
	virtual void OnAbilityTrigger(FGameplayTag TriggerTag) override;

	/* ICombatInterface */
	virtual bool HasActiveCombatAbility() override;
	virtual void RegisterCombatAbility(FGameplayTag AbilityTag, TSubclassOf<USLCombatAbility> CombatAbility) override;
	virtual void UnRegisterCombatAbility() override;
	virtual void Death() override;
};
