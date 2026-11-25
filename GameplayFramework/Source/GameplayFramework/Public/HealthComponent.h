// Copyright (c) 2026 PH Scherer. MIT License.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

/** Broadcast whenever health changes on any machine (server and clients). */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnHealthChanged, float, NewHealth, float, Delta);

/** Broadcast exactly once, when health reaches zero. */
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeath);

/**
 * Reusable health container for any gameplay entity: player, NPC, boss,
 * destructible prop or interactable world object.
 *
 * Responsibilities (and only these): current/max health, damage, healing,
 * death state and replication of that state.
 *
 * Network model: server authoritative. Clients never mutate health; they
 * observe it through replicated properties and react to the delegates. Every
 * public mutator is a no-op on clients.
 *
 * Usage (C++):
 *   HealthComponent->ApplyDamage(25.f);
 *   HealthComponent->OnDeath.AddDynamic(this, &AMyActor::HandleDeath);
 *
 * Usage (Blueprint): both delegates are assignable in the Details panel.
 */
UCLASS(ClassGroup = (GameplayFramework), BlueprintType, Blueprintable, meta = (BlueprintSpawnableComponent))
class GAMEPLAYFRAMEWORK_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UHealthComponent();

	// ---- Public API -------------------------------------------------------

	/**
	 * Applies damage. Server only. Ignores non-positive amounts and actors
	 * that are already dead.
	 * @return true when health changed (including the change that caused death).
	 */
	UFUNCTION(BlueprintCallable, Category = "Health", meta = (DisplayName = "Apply Damage"))
	bool ApplyDamage(float DamageAmount);

	/**
	 * Restores health, clamped to MaxHealth. Server only. Ignores non-positive
	 * amounts and actors that are already dead.
	 * @return true when health changed.
	 */
	UFUNCTION(BlueprintCallable, Category = "Health", meta = (DisplayName = "Apply Heal"))
	bool ApplyHeal(float HealAmount);

	/** Resets to MaxHealth, clears the dead flag and broadcasts OnHealthChanged. Server only. */
	UFUNCTION(BlueprintCallable, Category = "Health")
	void ResetHealth();

	// ---- Queries ----------------------------------------------------------

	/** Current health. On clients, the last value replicated from the server. */
	UFUNCTION(BlueprintPure, Category = "Health")
	float GetCurrentHealth() const { return CurrentHealth; }

	/** Maximum health. Replicated so clients never need to be told separately. */
	UFUNCTION(BlueprintPure, Category = "Health")
	float GetMaxHealth() const { return MaxHealth; }

	/** Current health as 0..1, ready for health bars. Returns 0 when MaxHealth <= 0. */
	UFUNCTION(BlueprintPure, Category = "Health")
	float GetHealthPercent() const;

	/** True once health reached zero (server). Mirrored to clients by replication. */
	UFUNCTION(BlueprintPure, Category = "Health")
	bool IsDead() const { return CurrentHealth <= 0.f; }

	// ---- Events -----------------------------------------------------------

	/** Fires on every machine whenever health changes. */
	UPROPERTY(BlueprintAssignable, Category = "Health|Events")
	FOnHealthChanged OnHealthChanged;

	/** Fires once when health reaches zero. */
	UPROPERTY(BlueprintAssignable, Category = "Health|Events")
	FOnDeath OnDeath;

protected:
	// ---- Lifecycle --------------------------------------------------------

	virtual void BeginPlay() override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	// ---- Authority helpers ------------------------------------------------

	/** Applies a signed delta on the server, clamps, and fires events exactly once on transition. */
	void TrySetHealth(float NewValue, float Delta);

	UFUNCTION()
	void OnRep_CurrentHealth(float PreviousHealth);

	// ---- Replicated state -------------------------------------------------

	/** Current health. Replicated with a callback so clients fire the same delegates as the server. */
	UPROPERTY(ReplicatedUsing = OnRep_CurrentHealth, BlueprintReadOnly, Category = "Health")
	float CurrentHealth = 0.f;

	/** Maximum health. Replicated so clients know the cap without extra RPCs. */
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadOnly, Category = "Health", meta = (ClampMin = "1.0", UIMin = "1.0"))
	float MaxHealth = 100.f;

private:
	/** Guards against broadcasting death more than once (server and each client). */
	bool bDeathBroadcast = false;
};