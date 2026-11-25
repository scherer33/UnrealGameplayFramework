# Interaction System

## Overview

Provides a unified interaction framework.

Players interact with objects through interfaces.

---

# Design Goal

Avoid object-specific interaction code.

---

# Interface

```cpp
IInteractable
```

---

# Supported Objects

- Doors
- Chests
- NPCs
- Terminals
- Switches
- Pickups

---

# Flow

```text
Player

↓

Trace

↓

Interactable Found

↓

Execute Interact()

↓

Result
```

---

# Benefits

- Reusable
- Extensible
- Decoupled

---

# Example

Adding a new object requires:

1. Implement Interface

No player code changes required.
