// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/GameResultWidget.h"

void UGameResultWidget::NativeConstruct()
{
	Super::NativeConstruct();

	GameResultText = Cast<UTextBlock>(GetWidgetFromName(TEXT("GameResultText")));
	ensure(GameResultText);
}

void UGameResultWidget::SetResultText(FText InText)
{
	GameResultText->SetText(InText);
}