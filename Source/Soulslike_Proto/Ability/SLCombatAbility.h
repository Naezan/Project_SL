// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "SLCombatAbility.generated.h"

DECLARE_DYNAMIC_DELEGATE(FOnEndAbilitySignature);

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class SOULSLIKE_PROTO_API USLCombatAbility : public UObject
{
	GENERATED_BODY()

public:
	APawn* GetOwningPawn() const;
	USkeletalMeshComponent* GetAvatarMeshComponent() const;
	UAnimInstance* GetAvatarAnimInstance() const;

public:
	virtual void TriggerAbility();
	virtual void EndAbility();
	virtual bool CanActivateAbility();
	virtual bool IsOverlappingAbility();


protected:
	void OnEndMontage(UAnimMontage* InMontage, bool bInterrupted);
	bool IsMontagePlaying();

public:
	FOnEndAbilitySignature OnEndAbilityDelegate;
	FOnMontageEnded OnCombatMontageEndDelegate;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Montage", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UAnimMontage> CombatMontage;
};
