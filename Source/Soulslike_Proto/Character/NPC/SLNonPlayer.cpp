// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/NPC/SLNonPlayer.h"
#include "AIController.h"
#include "BrainComponent.h"
#include "GameMode/SLGameMode.h"

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

	if (ASLGameMode* GM = Cast<ASLGameMode>(GetWorld()->GetAuthGameMode()))
	{
		GM->NPCDead();
	}
}

void ASLNonPlayer::DeathEnd()
{
	Super::DeathEnd();
}
