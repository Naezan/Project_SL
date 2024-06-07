// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/SLMainMenuController.h"
#include "Blueprint/UserWidget.h"

void ASLMainMenuController::BeginPlay()
{
	Super::BeginPlay();

    if (MainMenuWidgetClass)
    {
        MainMenuWidgetInstance = CreateWidget<UUserWidget>(GetWorld(), MainMenuWidgetClass);
        if (MainMenuWidgetInstance)
        {
            MainMenuWidgetInstance->AddToViewport();
        }
    }
}
