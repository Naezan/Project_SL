// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/HpBarWidget.h"
#include "Components/ProgressBar.h"

void UHpBarWidget::InitHpBar(float InCurrentHp, float InMaxHp)
{
	CurrentHp = InCurrentHp;
	MaxHp = InMaxHp;

	UpdateHpBar(CurrentHp);
}

void UHpBarWidget::UpdateHpBar(float InHp)
{
	CurrentHp = InHp;

	if (HpProgressBar)
	{
		HpProgressBar->SetPercent(CurrentHp / MaxHp);
	}
}

void UHpBarWidget::NativeConstruct()
{
	Super::NativeConstruct();

	HpProgressBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("HpProgressBar")));
	ensure(HpProgressBar);
}
