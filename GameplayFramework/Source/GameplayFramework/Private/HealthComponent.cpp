// Copyright (c) 2026 PH Scherer. MIT License.

#include "HealthComponent.h"
#include "Net/UnrealNetwork.h"
#include "Engine/World.h"

UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	PrimaryComponentTick.bStartWithTickEnabled = false;

	SetIsReplicatedByDefault(true);

	MaxHealth = 100.f;
	CurrentHealth = MaxHealth;
	bDeathBroadcast = false;
}

void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	if (GetOwner() && GetOwner()->HasAuthority())
	{
		CurrentHealth = MaxHealth;
		bDeathBroadcast = false;
	}
}

void UHealthComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UHealthComponent, CurrentHealth);
	DOREPLIFETIME(UHealthComponent, MaxHealth);
}

bool UHealthComponent::ApplyDamage(float DamageAmount)
{
	if (!GetOwner() || !GetOwner()->HasAuthority())
	{
		return false;
	}

	if (DamageAmount <= 0.f)
	{
		return false;
	}

	if (IsDead())
	{
		return false;
	}

	const float OldHealth = CurrentHealth;
	const float NewHealth = FMath::Max(0.f, CurrentHealth - DamageAmount);
	TrySetHealth(NewHealth, NewHealth - OldHealth);
	return !FMath::IsNearlyEqual(OldHealth, CurrentHealth, KINDA_SMALL_NUMBER);
}

bool UHealthComponent::ApplyHeal(float HealAmount)
{
	if (!GetOwner() || !GetOwner()->HasAuthority())
	{
		return false;
	}

	if (HealAmount <= 0.f)
	{
		return false;
	}

	if (IsDead())
	{
		return false;
	}

	const float OldHealth = CurrentHealth;
	const float NewHealth = FMath::Min(MaxHealth, CurrentHealth + HealAmount);
	TrySetHealth(NewHealth, NewHealth - OldHealth);
	return !FMath::IsNearlyEqual(OldHealth, CurrentHealth, KINDA_SMALL_NUMBER);
}

void UHealthComponent::ResetHealth()
{
	if (!GetOwner() || !GetOwner()->HasAuthority())
	{
		return;
	}

	const float OldHealth = CurrentHealth;
	CurrentHealth = MaxHealth;
	bDeathBroadcast = false;

	if (!FMath::IsNearlyEqual(OldHealth, CurrentHealth, KINDA_SMALL_NUMBER))
	{
		OnHealthChanged.Broadcast(CurrentHealth, CurrentHealth - OldHealth);
	}
}

float UHealthComponent::GetHealthPercent() const
{
	return MaxHealth > 0.f ? FMath::Clamp(CurrentHealth / MaxHealth, 0.f, 1.f) : 0.f;
}

void UHealthComponent::TrySetHealth(float NewValue, float Delta)
{
	if (!GetOwner() || !GetOwner()->HasAuthority())
	{
		return;
	}

	const float Clamped = FMath::Clamp(NewValue, 0.f, MaxHealth);
	if (FMath::IsNearlyEqual(Clamped, CurrentHealth, KINDA_SMALL_NUMBER))
	{
		return;
	}

	CurrentHealth = Clamped;
	OnHealthChanged.Broadcast(CurrentHealth, Delta);

	if (CurrentHealth <= KINDA_SMALL_NUMBER && !bDeathBroadcast)
	{
		bDeathBroadcast = true;
		OnDeath.Broadcast();
	}
}

void UHealthComponent::OnRep_CurrentHealth(float PreviousHealth)
{
	const float Delta = CurrentHealth - PreviousHealth;
	OnHealthChanged.Broadcast(CurrentHealth, Delta);

	if (CurrentHealth <= KINDA_SMALL_NUMBER && !bDeathBroadcast)
	{
		bDeathBroadcast = true;
		OnDeath.Broadcast();
	}
}
