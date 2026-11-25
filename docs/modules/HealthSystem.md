# Health System

## Overview

The Health System is designed as a reusable Actor Component that can be attached to any gameplay entity.

Supported actors:

- Players
- NPCs
- Bosses
- Destructible Objects
- Interactive World Objects

The component is responsible for health management only.

---

# Features

- Damage Processing
- Healing
- Death Events
- Max Health Configuration
- Health Replication
- Event Broadcasting

---

# Architecture

```text
Character
    │
    ▼
Health Component
    │
    ├── Current Health
    ├── Max Health
    ├── Damage
    ├── Healing
    └── Death Logic
```

---

# Public API

## Damage

```cpp
ApplyDamage(float DamageAmount)
```

Applies incoming damage.

---

## Heal

```cpp
ApplyHeal(float HealAmount)
```

Restores health.

---

## Death

```cpp
HandleDeath()
```

Executes death logic.

---

# Delegates

```cpp
OnHealthChanged

OnDeath
```

These events allow external systems to react.

Examples:

- HUD
- Quest Logic
- Achievement System
- Audio Feedback

---

# Replication

CurrentHealth is replicated.

The server is authoritative.

Clients receive updates automatically.

---

# Design Principles

- Single Responsibility
- Event Driven
- Multiplayer Compatible
- Reusable Across Projects
