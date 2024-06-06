// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "SLCharacterBase.generated.h"

UCLASS(config=Game)
class ASLCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	ASLCharacterBase();
};

