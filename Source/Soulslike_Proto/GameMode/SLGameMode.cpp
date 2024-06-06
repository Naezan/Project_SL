// Copyright Epic Games, Inc. All Rights Reserved.

#include "SLGameMode.h"
#include "Character/SLCharacterBase.h"
#include "UObject/ConstructorHelpers.h"

ASLGameMode::ASLGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Soulslike/Blueprints/BP_Player"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
