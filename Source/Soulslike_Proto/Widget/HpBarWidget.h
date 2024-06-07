// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HpBarWidget.generated.h"

/**
 * 
 */
UCLASS()
class SOULSLIKE_PROTO_API UHpBarWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void InitHpBar(float InCurrentHp, float InMaxHp);
	void UpdateHpBar(float InHp);

protected:
	virtual void NativeConstruct() override;

protected:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<class UProgressBar> HpProgressBar;

	UPROPERTY()
	float MaxHp;
	UPROPERTY()
	float CurrentHp;
};
