# Roadmap

This project is developed in phases. Each phase delivers something usable on its own —
no phase depends on starting another one from scratch.

---

# Phase 0 — Design (current)

Written specs for every module. This repository, today.

- [x] Health System spec
- [x] Weapon Framework spec
- [x] Inventory System spec
- [x] Interaction System spec
- [x] AI Framework spec
- [x] Multiplayer Architecture spec
- [x] Coding Standards
- [x] Optimization Guide

---

# Phase 1 — C++ Core

First playable foundation. Small, reusable components with no cross-dependencies.

- [ ] `UHealthComponent` — damage, healing, death, replication
- [ ] `IInteractable` interface + player interaction trace
- [ ] Project plugin structure (`Plugins/GameplayFramework`)
- [ ] Automated tests for the components above

---

# Phase 2 — Items & Weapons

- [ ] Data-Asset-driven item definitions
- [ ] `UInventoryComponent` — add, remove, stack, equip
- [ ] Weapon base class + first weapon types (rifle, pistol)
- [ ] Server-validated firing and replication

---

# Phase 3 — Input, UI & Persistence

- [ ] Enhanced Input integration
- [ ] HUD hooks driven by delegates (no polling)
- [ ] Save system: slots and cross-platform persistence

---

# Phase 4 — Gameplay Ability System

- [ ] GAS integration: abilities, effects, attributes
- [ ] Gameplay Tags across modules
- [ ] Migration of health to GAS attributes (behind the same public API)

---

# Phase 5 — AI & Dedicated Servers

- [ ] Squad AI, tactical decisions, cover usage
- [ ] Dedicated servers
- [ ] Matchmaking and session management

---

# Phase 6 — UEFN (research)

- [ ] Evaluate UEFN / Verse / Fortnite Creative adaptation
- [ ] Feasibility report before any implementation

---

# Beyond the phases

Ideas that may land in any phase, ordered by demand:

- Weapon attachments, mods, recoil and spread patterns
- Trading, crafting, storage containers, currency
- Advanced ballistics
