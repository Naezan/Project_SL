// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SLPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class SOULSLIKE_PROTO_API ASLPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	void GameClear();
	void GameOver();

protected:
	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<UUserWidget> GameResultWidgetClass;
};
