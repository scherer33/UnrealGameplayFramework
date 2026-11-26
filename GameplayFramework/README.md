# GameplayFramework (Unreal Engine plugin)

Phase 1 C++ core of the [Unreal Gameplay Framework](../README.md).
Drop-in plugin for **Unreal Engine 5.5**.

## What's in phase 1

| Type | File | Purpose |
| --- | --- | --- |
| `UHealthComponent` | `Source/GameplayFramework/Public/HealthComponent.h` | Replicated, server-authoritative health: damage, healing, death and delegates |
| `IInteractable` | `Source/GameplayFramework/Public/Interactable.h` | Blueprint-native interface for anything a player can interact with |

The player-side interaction trace (`UInteractionComponent`) is **phase 2** and is not here yet.

## Install

1. Copy this whole folder into your project:

   ```text
   MyProject/
   └── Plugins/
       └── GameplayFramework/
   ```

2. Regenerate project files (right-click the `.uproject` -> *Generate Visual Studio project files*,
   or run `Build.sh` / `GenerateProjectFiles` for your IDE).

3. Build and open the editor. The plugin is `Runtime`, `Default` loading phase and does not need
   to be enabled manually — it compiles with your project.

## Use the health component

C++:

```cpp
UHealthComponent* Health = CreateDefaultSubobject<UHealthComponent>(TEXT("Health"));
Health->MaxHealth = 150.f;
Health->OnHealthChanged.AddDynamic(this, &AMyActor::HandleHealthChanged);
Health->OnDeath.AddDynamic(this, &AMyActor::HandleDeath);
```

Blueprint:

1. Add the **Health** component to any actor (player, NPC, boss, destructible, prop).
2. Set **Max Health** in the Details panel.
3. Assign **On Health Changed** (New Health, Delta) and **On Death** events.

Damage and healing must be called on the server:

```cpp
Health->ApplyDamage(25.f);  // returns true when health changed
Health->ApplyHeal(10.f);    // clamped to MaxHealth
```

Clients never call these; they react to the delegates when the server replicates `CurrentHealth`.
`OnDeath` fires exactly once per life. `ResetHealth()` handles respawns.

## Use the interactable interface

C++ — implement the interface on your actor and override the native events:

```cpp
UCLASS()
class ADoor : public AActor, public IInteractable
{
	GENERATED_BODY()

	virtual bool CanInteract_Implementation(AActor* Interactor) const override { return !bIsOpen; }
	virtual void Interact_Implementation(AActor* Interactor) override { Open(); }
};
```

Blueprint — *Class Settings -> Interfaces -> Interactable*. The interface supplies
`CanInteract` (returns `true` by default) and `Interact` (no-op by default). **Override them.**

> Mutations must be validated on the authority: return early in `Interact_Implementation`
> with `if (!HasAuthority()) { return; }`, or drive the effect with replication.

## Tests

`Tests/HealthComponentTests.cpp` holds Unreal Automation Tests. They are **not compiled as part
of the plugin** — copy the file into a test module of a project that references this plugin,
then run:

```bash
UnrealEditor <Project>.uproject \
  -ExecCmds="Automation RunTests GameplayFramework.Health; Quit" \
  -unattended -nopause -nullrhi
```

The tests only assert state transitions (damage/heal/death), so they run without a graphical
editor (`-nullrhi`).

## Network model

- `CurrentHealth` is `ReplicatedUsing=OnRep_CurrentHealth`; clients fire `OnHealthChanged` and
  `OnDeath` from the replicated value, so HUD, audio, quests and achievements react on both ends.
- `MaxHealth` is replicated so clients know the cap without extra RPCs.
- The component does not tick. It never replicates a per-frame value.

## Compatibility

Tested against the UE 5.5 API surface only. If you compile against another version, check the
`UActorComponent`/replication headers and remove the plugin from the project if you need a
different major.
