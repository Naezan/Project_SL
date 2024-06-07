// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/SLAIController.h"
#include "AI/SLAIPerceptionComponent.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AIPerceptionSystem.h"
#include "Perception/AISenseConfig.h"
#include "Perception/AISense_Sight.h"

ASLAIController::ASLAIController()
{
	AIPerceptionComponent = CreateDefaultSubobject<USLAIPerceptionComponent>("AIPerceptionComponent");
}

void ASLAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (BTAsset != nullptr)
	{
		RunBehaviorTree(BTAsset);
	}

	if (AIPerceptionComponent != nullptr)
	{
		AIPerceptionComponent->RequestStimuliListenerUpdate();

		AIPerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &ASLAIController::OnTargetPerceptionUpdated);
		AIPerceptionComponent->OnStimuliExpired.AddDynamic(this, &ASLAIController::OnStimuliExpired);
	}
}

void ASLAIController::OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	if (UBlackboardComponent* BBComponent = GetBlackboardComponent())
	{
		TSubclassOf<UAISense> AISence = UAIPerceptionSystem::GetSenseClassForStimulus(GetWorld(), Stimulus).Get();

		if (AISence == UAISense_Sight::StaticClass())
		{
			BBComponent->SetValueAsObject(TEXT("AttackTarget"), Actor);
		}
	}
}

void ASLAIController::OnStimuliExpired(const FAIStimulus& Stimulus)
{
	TSubclassOf<UAISense> AISence = UAIPerceptionSystem::GetSenseClassForStimulus(GetWorld(), Stimulus).Get();

	if (AISence == UAISense_Sight::StaticClass())
	{
		// 다시 제자리로
	}
}