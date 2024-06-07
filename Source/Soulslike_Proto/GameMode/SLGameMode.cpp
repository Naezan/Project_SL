// Copyright Epic Games, Inc. All Rights Reserved.

#include "SLGameMode.h"
#include "UObject/ConstructorHelpers.h"
#include "Character/SLPlayerController.h"

ASLGameMode::ASLGameMode()
{
}

void ASLGameMode::NPCDead()
{
	if (ASLPlayerController* PC = Cast<ASLPlayerController>(GetWorld()->GetFirstPlayerController()))
	{
		PC->GameClear();
	}
}

void ASLGameMode::PlayerDead()
{
	if (ASLPlayerController* PC = Cast<ASLPlayerController>(GetWorld()->GetFirstPlayerController()))
	{
		PC->GameOver();
	}
}
