// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Player/SLPlayer.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Input/SLInputComponent.h"
#include "Character/SLCombatComponent.h"
#include "Character/SLStatComponent.h"

ASLPlayer::ASLPlayer()
{
	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	ExtInputComponent = CreateDefaultSubobject<USLInputComponent>(TEXT("InputComponent"));
	CombatComponent = CreateDefaultSubobject<USLCombatComponent>(TEXT("CombatComponent"));
	StatComponent = CreateDefaultSubobject<USLStatComponent>(TEXT("StatComponent"));
}

void ASLPlayer::SetupPlayerInputComponent(UInputComponent* InPlayerInputComponent)
{
	Super::SetupPlayerInputComponent(InPlayerInputComponent);

	if (ExtInputComponent != nullptr)
	{
		ExtInputComponent->SetupInputComponent(InPlayerInputComponent);
	}
}

void ASLPlayer::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if (CombatComponent != nullptr)
	{
		CombatComponent->RegisterAbility();
	}
}

void ASLPlayer::BeginDestroy()
{
	if (CombatComponent != nullptr)
	{
		CombatComponent->UnRegisterAbility();
	}

	Super::BeginDestroy();
}

float ASLPlayer::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	return Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
}

void ASLPlayer::OnAbilityTrigger(FGameplayTag TriggerTag)
{
	if (CombatComponent != nullptr)
	{
		CombatComponent->OnActivateAbility(TriggerTag);
	}
}

bool ASLPlayer::HasActiveCombatAbility()
{
	if (CombatComponent != nullptr)
	{
		return CombatComponent->HasActiveAbility();
	}

	return false;
}

void ASLPlayer::Death()
{
	if (CombatComponent != nullptr)
	{
		CombatComponent->OnDeActivateAbility();
	}
}
