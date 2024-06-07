// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "SLAnimInstance.generated.h"

class ACharacter;
class UCharacterMovementComponent;

/**
 * 
 */
UCLASS()
class SOULSLIKE_PROTO_API USLAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

protected:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds) override;

private:
	void UpdateMovementData();
	
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<ACharacter> Character;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component|Movement", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCharacterMovementComponent> CharacterMovement;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	FVector Velocity;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	float GroundSpeed;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	uint8 bShouldMove : 1;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	uint8 bIsFalling : 1;
};
