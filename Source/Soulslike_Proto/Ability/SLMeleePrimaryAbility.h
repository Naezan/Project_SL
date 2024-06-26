// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ability/SLCombatAbility.h"
#include "SLMeleePrimaryAbility.generated.h"

USTRUCT(BlueprintType)
struct FComboSectionInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName CurveName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FName> SectionNames;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 CurrentSectionIndex = 0;

public:
	void ResetIndex();
	const FName GetCurrentSectionName();
	void IncreatementSection();
};

USTRUCT(BlueprintType)
struct FAttackInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	FName NotifyName;

	UPROPERTY(EditAnywhere)
	float WidthRange;

	UPROPERTY(EditAnywhere)
	float DepthRange;
};

/**
 * 
 */
UCLASS()
class SOULSLIKE_PROTO_API USLMeleePrimaryAbility : public USLCombatAbility
{
	GENERATED_BODY()

public:
	virtual void TriggerAbility() override;
	virtual void EndAbility() override;
	virtual bool IsOverlappingAbility() override;

protected:
	virtual void OnNotifyBegin(FName NotifyName) override;

private:
	bool CanChangeComboSection();
	void MoveToNextComboSection();

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Combo", meta = (AllowPrivateAccess = "true"))
	FComboSectionInfo ComboSectionInfo;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Combo|Attack", meta = (AllowPrivateAccess = "true"))
	FAttackInfo AttackInfo;
};
