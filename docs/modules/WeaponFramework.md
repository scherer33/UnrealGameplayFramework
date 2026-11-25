# Weapon Framework

## Overview

The Weapon Framework provides a flexible architecture for creating multiple weapon types.

---

# Goals

Support:

- Pistols
- Rifles
- Shotguns
- Snipers
- Melee Weapons

without modifying existing code.

---

# Architecture

```text
WeaponBase

├── RifleWeapon
├── ShotgunWeapon
├── SniperWeapon
├── PistolWeapon
└── MeleeWeapon
```

---

# Core Features

## Fire

```cpp
Fire()
```

---

## Reload

```cpp
Reload()
```

---

## Stop Fire

```cpp
StopFire()
```

---

# Weapon Data

Every weapon contains:

```text
Damage
Ammo
Magazine Size
Reload Time
Fire Rate
Range
```

---

# Replication

Replicated Data:

- Ammo
- Current Weapon
- Reload State

Server validates all shots.

---

# Future Features

- Weapon Attachments
- Weapon Mods
- Recoil System
- Spread Patterns
- Advanced Ballistics

---

# Design Patterns

Pattern Used:

Factory Pattern

New weapons can be created without modifying existing systems.
