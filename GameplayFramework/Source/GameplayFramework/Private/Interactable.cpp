// Copyright (c) 2026 PH Scherer. MIT License.

#include "Interactable.h"

bool IInteractable::CanInteract_Implementation(AActor* Interactor) const
{
	// Open by default: most objects are interactable. Override to lock behavior.
	return true;
}

void IInteractable::Interact_Implementation(AActor* Interactor)
{
	// Intentional no-op: concrete interactables (doors, chests, NPCs, ...
	// implement the effect. Blueprints override the interface event directly.
}
