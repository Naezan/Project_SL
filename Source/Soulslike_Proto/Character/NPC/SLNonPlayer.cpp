// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/NPC/SLNonPlayer.h"
#include "AIController.h"
#include "BrainComponent.h"

ASLNonPlayer::ASLNonPlayer()
{
}

void ASLNonPlayer::DeathStart()
{
	if (AAIController* NPCController = Cast<AAIController>(GetController()))
	{
		NPCController->GetBrainComponent()->StopLogic(FString("Death"));
	}

	Super::DeathStart();
}

void ASLNonPlayer::DeathEnd()
{
	Super::DeathEnd();
}
