// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "GameResultWidget.generated.h"

/**
 * 
 */
UCLASS()
class SOULSLIKE_PROTO_API UGameResultWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void SetResultText(FText InText);

protected:
	virtual void NativeConstruct() override;

protected:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<class UTextBlock> GameResultText;
};
