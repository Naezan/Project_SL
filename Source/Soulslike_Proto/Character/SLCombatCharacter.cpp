// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/SLCombatCharacter.h"
#include "Attribute/SLStatComponent.h"
#include "Combat/SLCombatComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/WidgetComponent.h"
#include "Equipment/SLEquipmentComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Widget/HpBarWidget.h"

ASLCombatCharacter::ASLCombatCharacter()
{
	CombatComponent = CreateDefaultSubobject<USLCombatComponent>(TEXT("CombatComponent"));
	EquipComponent = CreateDefaultSubobject<USLEquipmentComponent>(TEXT("EquipComponent"));
	StatComponent = CreateDefaultSubobject<USLStatComponent>(TEXT("AttributeComponent"));

	HpWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("HpWidget"));
	HpWidget->SetupAttachment(GetMesh());
	HpWidget->SetRelativeLocation(FVector(0.0f, 0.0f, 180.0f));
	HpWidget->SetWidgetSpace(EWidgetSpace::Screen);
	HpWidget->SetDrawSize(FVector2D(150.0f, 15.0f));
	HpWidget->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	if (HpWidgetClass)
	{
		HpWidget->SetWidgetClass(HpWidgetClass);
	}
}

void ASLCombatCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (StatComponent != nullptr)
	{
		StatComponent->InitAttribute();

		InitHpBarWidget();
	}

	if (CombatComponent != nullptr)
	{
		CombatComponent->RegisterDefualtAbilities();
	}

	if (EquipComponent != nullptr)
	{
		EquipComponent->EquipOnStart();
	}
}

void ASLCombatCharacter::OnAbilityTrigger(FGameplayTag TriggerTag)
{
	if (CombatComponent != nullptr)
	{
		CombatComponent->OnActivateAbility(TriggerTag);
	}
}

void ASLCombatCharacter::SetAbilityEndDelegate(const FOnAbilityEndDelegate& InAbilityEndDelegate)
{
	OnAbilityEndDelegate = InAbilityEndDelegate;
}

void ASLCombatCharacter::ExecuteOnAbilityEndDelegate()
{
	OnAbilityEndDelegate.ExecuteIfBound();
}

bool ASLCombatCharacter::HasActiveCombatAbility()
{
	if (CombatComponent != nullptr)
	{
		return CombatComponent->HasActiveAbility();
	}

	return false;
}

void ASLCombatCharacter::RegisterCombatAbility(FGameplayTag AbilityTag, TSubclassOf<USLCombatAbility> CombatAbility)
{
	if (CombatComponent != nullptr)
	{
		CombatComponent->RegisterAbility(AbilityTag, CombatAbility);
	}
}

void ASLCombatCharacter::UnRegisterCombatAbility(FGameplayTag AbilityTag)
{
	if (CombatComponent != nullptr)
	{
		CombatComponent->UnRegisterAbility(AbilityTag);
	}
}

void ASLCombatCharacter::RegisterWeaponAttribute(FWeaponAttributeInfo WeaponAttribute)
{
	if (StatComponent != nullptr)
	{
		StatComponent->InitAttackDamage(WeaponAttribute.Damage);
	}
}

void ASLCombatCharacter::UnRegisterWeaponAttribute()
{
	if (StatComponent != nullptr)
	{
		StatComponent->ResetAttribute();
	}
}

void ASLCombatCharacter::ApplyWeaponDamage(AActor* DamageVictim, TSubclassOf<UDamageType> DamageTypeClass)
{
	if (StatComponent != nullptr)
	{
		UGameplayStatics::ApplyDamage(DamageVictim, StatComponent->GetAttackDamage(), GetController(), this, DamageTypeClass);
	}
}

void ASLCombatCharacter::DeathStart()
{
	if (CombatComponent != nullptr)
	{
		CombatComponent->OnEndAbility();
	}

	if (EquipComponent != nullptr)
	{
		EquipComponent->UnEquip();
	}

	if (CombatComponent != nullptr)
	{
		CombatComponent->DeathStart();
	}

	if (HpWidget != nullptr)
	{
		HpWidget->SetWidget(nullptr);
	}

	if (UCapsuleComponent* CapsuleComp = GetCapsuleComponent())
	{
		CapsuleComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		CapsuleComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	}
}

void ASLCombatCharacter::DeathEnd()
{
	if (CombatComponent != nullptr)
	{
		CombatComponent->UnRegisterAllAbilities();
	}

	GetCharacterMovement()->StopMovementImmediately();

	RagDoll();
}

void ASLCombatCharacter::RagDoll()
{
	GetMesh()->SetCollisionProfileName(FName("Ragdoll"));
	GetMesh()->SetSimulatePhysics(true);
	GetMesh()->SetAllBodiesBelowSimulatePhysics(FName("pelvis"), true, true);
}

float ASLCombatCharacter::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float TotalDamage = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

	if (StatComponent != nullptr)
	{
		float Health = StatComponent->ApplyAttackDamage(TotalDamage);

		if (FMath::IsNearlyZero(Health))
		{
			DeathStart();
			return TotalDamage;
		}
	}

	if (CombatComponent != nullptr)
	{
		CombatComponent->PlayHitMontage(DamageCauser);
	}

	return TotalDamage;
}

void ASLCombatCharacter::InitHpBarWidget()
{
	if (UHpBarWidget* HpBarWidget = Cast<UHpBarWidget>(HpWidget->GetWidget()))
	{
		HpBarWidget->InitHpBar(StatComponent->GetHealth(), StatComponent->GetMaxHealth());
		StatComponent->OnHealthChanged.BindUObject(HpBarWidget, &UHpBarWidget::UpdateHpBar);
	}
}
