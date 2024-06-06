// Fill out your copyright notice in the Description page of Project Settings.


#include "Input/SLInputComponent.h"
#include "GameFramework/Character.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Ability/AbilityControlInterface.h"
#include "Character/CombatInterface.h"

// Sets default values for this component's properties
USLInputComponent::USLInputComponent()
{
	
}


// Called when the game starts
void USLInputComponent::BeginPlay()
{
	Super::BeginPlay();

	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

void USLInputComponent::SetupInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {

		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &USLInputComponent::StartJump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &USLInputComponent::StopJump);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &USLInputComponent::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &USLInputComponent::Look);

		for (const auto& InputInfo : AbilityInputActionMap)
		{
			EnhancedInputComponent->BindAction(InputInfo.Value, ETriggerEvent::Triggered, this, &USLInputComponent::AbilityInputPressed, InputInfo.Key);
		}
	}
}

void USLInputComponent::StartJump()
{
	if (ICombatInterface* CombatInterface = Cast<ICombatInterface>(GetPawn()))
	{
		if (CombatInterface->HasActiveCombatAbility())
		{
			return;
		}
	}

	if (ACharacter* OwningCharacter = Cast<ACharacter>(GetPawn()))
	{
		OwningCharacter->Jump();
	}
}

void USLInputComponent::StopJump()
{
	if (ACharacter* OwningCharacter = Cast<ACharacter>(GetPawn()))
	{
		OwningCharacter->StopJumping();
	}
}

void USLInputComponent::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (AController* OwningController = GetController())
	{
		// find out which way is forward
		const FRotator Rotation = OwningController->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		if (APawn* OwningPawn = GetPawn())
		{
			// add movement 
			OwningPawn->AddMovementInput(ForwardDirection, MovementVector.Y);
			OwningPawn->AddMovementInput(RightDirection, MovementVector.X);
		}
	}
}

void USLInputComponent::Look(const FInputActionValue& Value)
{
	check(GetController());

	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (APawn* OwningPawn = GetPawn())
	{
		// add yaw and pitch input to controller
		OwningPawn->AddControllerYawInput(LookAxisVector.X);
		OwningPawn->AddControllerPitchInput(LookAxisVector.Y);
	}
}

void USLInputComponent::AbilityInputPressed(FGameplayTag InputTag)
{
	if (IAbilityControlInterface* OwningCharacter = Cast<IAbilityControlInterface>(GetPawn()))
	{
		OwningCharacter->OnAbilityTrigger(InputTag);
	}
}

