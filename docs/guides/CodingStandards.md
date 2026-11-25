# Coding Standards

## Goals

- Consistency
- Readability
- Scalability

---

# Naming

## Actors

```cpp
APlayerCharacter
```

---

## Components

```cpp
UHealthComponent
```

---

## Interfaces

```cpp
IInteractable
```

---

# Best Practices

Use:

- Components
- Interfaces
- Delegates

Avoid:

- God Classes
- Massive Tick Functions
- Tight Coupling

---

# Function Design

Functions should:

- Do One Thing
- Be Predictable
- Be Easy to Test

---

# Comments

Explain WHY.

Not WHAT.

Bad:

```cpp
// Add Damage
```

Good:

```cpp
// Damage is clamped to prevent negative health values.
```
