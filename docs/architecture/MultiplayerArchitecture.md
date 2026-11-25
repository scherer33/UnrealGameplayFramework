# Multiplayer Architecture

## Overview

This framework is designed with multiplayer support from the beginning.

---

# Core Principle

Server Authority

The server is responsible for validating critical gameplay actions.

---

# Client-Server Model

```text
Client

↓

Request

↓

Server

↓

Validation

↓

Replication

↓

All Clients
```

---

# Replicated Systems

## Health

Replicated.

---

## Weapons

Replicated.

---

## Inventory

Replicated.

---

## Character State

Replicated.

---

# RPC Usage

Server RPC

```cpp
ServerFireWeapon()
```

Client RPC

```cpp
ClientReceiveDamage()
```

Multicast RPC

```cpp
MulticastPlayFX()
```

---

# Benefits

- Reduced cheating
- Network consistency
- Competitive fairness
