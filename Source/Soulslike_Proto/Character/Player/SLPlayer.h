// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/SLCombatCharacter.h"
#include "SLPlayer.generated.h"

class USpringArmComponent;
class UCameraComponent;
class USLInputComponent;
class UAIPerceptionStimuliSourceComponent;

class USLCombatAbility;

/**
 *
 */
UCLASS()
class SOULSLIKE_PROTO_API ASLPlayer : public ASLCombatCharacter
{
	GENERATED_BODY()

public:
	ASLPlayer();

protected:
	virtual void SetupPlayerInputComponent(class UInputComponent* InPlayerInputComponent) override;


public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

private:
	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component|Input", meta = (AllowPrivateAccess = "true"))
	USLInputComponent* ExtInputComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Component|AI", Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UAIPerceptionStimuliSourceComponent> AIPerceptionStimuliSourceComponent;
};
