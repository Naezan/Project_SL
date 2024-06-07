// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Player/SLPlayer.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Input/SLInputComponent.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"

ASLPlayer::ASLPlayer()
{
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f;
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	ExtInputComponent = CreateDefaultSubobject<USLInputComponent>(TEXT("InputComponent"));
	AIPerceptionStimuliSourceComponent = CreateDefaultSubobject<UAIPerceptionStimuliSourceComponent>(TEXT("AIPerceptionStimuliSource"));
}

void ASLPlayer::SetupPlayerInputComponent(UInputComponent* InPlayerInputComponent)
{
	Super::SetupPlayerInputComponent(InPlayerInputComponent);

	if (ExtInputComponent != nullptr)
	{
		ExtInputComponent->SetupInputComponent(InPlayerInputComponent);
	}
}

void ASLPlayer::DeathStart()
{
	Super::DeathStart();

	if (APlayerController* OwningController = Cast<APlayerController>(GetController()))
	{
		DisableInput(OwningController);
	}
}

void ASLPlayer::DeathEnd()
{
	Super::DeathEnd();
}
