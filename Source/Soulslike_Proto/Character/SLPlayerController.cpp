// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/SLPlayerController.h"
#include "Widget/GameResultWidget.h"

void ASLPlayerController::GameClear()
{
    if (GameResultWidgetClass)
    {
        if (UGameResultWidget* WidgetInstance = CreateWidget<UGameResultWidget>(GetWorld(), GameResultWidgetClass))
        {
            WidgetInstance->AddToViewport();

            WidgetInstance->SetResultText(FText::FromString("GameClear"));
        }
    }
}

void ASLPlayerController::GameOver()
{
    if (GameResultWidgetClass)
    {
        if (UGameResultWidget* WidgetInstance = CreateWidget<UGameResultWidget>(GetWorld(), GameResultWidgetClass))
        {
            WidgetInstance->AddToViewport();

            WidgetInstance->SetResultText(FText::FromString("GameOver"));
        }
    }
}
