// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameFramework/Pawn.h"
#include "PawnComponent.generated.h"


UCLASS()
class SOULSLIKE_PROTO_API UPawnComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UPawnComponent();

	APawn* GetPawn() const
	{
		return Cast<APawn>(GetOwner());
	}

	APawn* GetChackedPawn() const
	{
		return CastChecked<APawn>(GetOwner());
	}

	APlayerState* GetPlayerState() const
	{
		return GetChackedPawn()->GetPlayerState();
	}

	AController* GetController() const
	{
		return GetChackedPawn()->GetController();
	}
};
