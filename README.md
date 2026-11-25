# Unreal Gameplay Framework

Design-first gameplay framework for **Unreal Engine 5** — a collection of modular,
multiplayer-ready systems specified before a single line of gameplay code is written.

> **Status:** design phase. This repository currently contains the architecture specs.
> The C++ implementation lands incrementally according to the [roadmap](docs/ROADMAP.md).

---

## Why design first

Gameplay code rots fast when systems are coupled. Every module here starts as a written
spec that answers the same questions up front:

- What is the module **responsible** for — and explicitly not responsible for?
- Where does authority live in a **client-server** model?
- How do other systems react without touching the internals (events, interfaces, components)?
- What is the **public API** before implementation?

The result is a set of small, composable systems that a team can implement, test and
extend without coordination overhead.

---

## Modules

| Module | Responsibility | Spec |
| --- | --- | --- |
| **Health** | Damage, healing, death for any actor via a reusable component | [HealthSystem](docs/modules/HealthSystem.md) |
| **Weapon** | Data-driven weapons with a shared base and per-type subclasses | [WeaponFramework](docs/modules/WeaponFramework.md) |
| **Inventory** | Items, equipment and stacking driven by Data Assets | [InventorySystem](docs/modules/InventorySystem.md) |
| **Interaction** | One interface for every interactable object | [InteractionSystem](docs/modules/InteractionSystem.md) |
| **AI** | AIController + Behavior Tree + Blackboard + Perception | [AIFramework](docs/modules/AIFramework.md) |

## Architecture & guides

- [Multiplayer Architecture](docs/architecture/MultiplayerArchitecture.md) — server authority, replication, RPC policy
- [Coding Standards](docs/guides/CodingStandards.md) — naming, best practices, function design
- [Optimization Guide](docs/guides/OptimizationGuide.md) — profiling first, tick budget, networking cost

## Design principles

- **Single Responsibility** — components do one thing (the health component manages health only).
- **Event-driven** — systems react through delegates (`OnHealthChanged`, `OnDeath`); no polling.
- **Server authority** — the server validates critical actions; clients trust replication.
- **Reusable across projects** — no single-game assumptions baked into the systems.
- **Designers first** — tuning lives in Data Assets, not in code.

## Roadmap

| Phase | Scope |
| --- | --- |
| 0 | Written specs for every module (this repo today) |
| 1 | C++ core: Health, Interaction components |
| 2 | Inventory & Weapon framework on top of the core |
| 3 | Enhanced Input integration, UI hooks, save system |
| 4 | Gameplay Ability System (GAS) integration |
| 5 | AI squads, tactical decisions, dedicated servers / matchmaking |
| 6 | UEFN / Verse adaptation — research only |

Full detail in [docs/ROADMAP.md](docs/ROADMAP.md).

---

## Repository structure

```text
docs/
├── ROADMAP.md              # planned work, phase by phase
├── architecture/
│   └── MultiplayerArchitecture.md
├── guides/
│   ├── CodingStandards.md
│   └── OptimizationGuide.md
└── modules/
    ├── HealthSystem.md
    ├── WeaponFramework.md
    ├── InventorySystem.md
    ├── InteractionSystem.md
    └── AIFramework.md
```

## License

[MIT](LICENSE)
