// Copyright (c) 2026 PH Scherer. MIT License.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Interactable.generated.h"

/**
 * UInteractable
 *
 * Empty UInterface used only to drive reflection for IInteractable.
 * Put your C++ implementation on the actor (see README).
 */
UINTERFACE(MinimalAPI, Blueprintable, BlueprintType)
class UInteractable : public UInterface
{
	GENERATED_BODY()
};

/**
 * Anything a player can interact with: doors, chests, NPCs, terminals, pickups.
 *
 * Implement this interface in C++ (multiple inheritance) or in Blueprints
 * (Class Settings -> Interfaces -> Interactable), and override the Interact event
 * from your own Blueprint.
 *
 * Network policy: mutations must be validated on the authority. Follow this
 * pattern in Interact_Implementation:
 *
 *   if (!HasAuthority()) { return; }
 *   // Server-only game effect...
 *
 * The player-side trace that decides "which actor is under the crosshair" ships
 * in Phase 2 as a separate component.
 */
class GAMEPLAYFRAMEWORK_API IInteractable
{
	GENERATED_BODY()

public:
	/**
	 * Whether the given actor may interact with this object right now.
	 * Defaults to true. Override for locks, cooldowns, full inventories, etc.
	 *
	 * @param Interactor  The actor attempting to interact (usually a pawn).
	 * @return true when the interaction should be allowed.
	 */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
	bool CanInteract(AActor* Interactor) const;

	/**
	 * Performs the interaction. Defaults to a no-op.
	 *
	 * Server authoritative: the default design requires this to be invoked on
	 * the server. For example, the Interact event can be Replicated from the
	 * player, or called from a Server RPC, then let replication drive the
	 * client visuals.
	 *
	 * Callers must check CanInteract first.
	 *
	 * @param Interactor  The actor attempting to interact (usually a pawn).
	 */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
	void Interact(AActor* Interactor);
};
