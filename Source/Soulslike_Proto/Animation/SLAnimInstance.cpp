// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/SLAnimInstance.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

void USLAnimInstance::NativeInitializeAnimation()
{
	Character = Cast<ACharacter>(TryGetPawnOwner());
	CharacterMovement = Character ? Character->GetCharacterMovement() : nullptr;
}

void USLAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	UpdateMovementData();
}

void USLAnimInstance::UpdateMovementData()
{
	if (CharacterMovement != nullptr)
	{
		Velocity = CharacterMovement->Velocity;
		GroundSpeed = Velocity.Size2D();

		bShouldMove = (GroundSpeed > 3.f) && (!CharacterMovement->GetCurrentAcceleration().IsNearlyZero());
		bIsFalling = CharacterMovement->IsFalling();
	}
}
