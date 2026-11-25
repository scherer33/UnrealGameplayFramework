# Inventory System

## Overview

The Inventory System manages item storage and equipment.

---

# Features

- Add Items
- Remove Items
- Equip Items
- Consume Items
- Stack Items

---

# Architecture

```text
InventoryComponent

├── Weapons
├── Consumables
├── Quest Items
└── Equipment
```

---

# Item Representation

Items are Data Asset driven.

Benefits:

- Easier balancing
- Better designer workflow
- Less hardcoded content

---

# Core Functions

```cpp
AddItem()

RemoveItem()

UseItem()

EquipItem()
```

---

# Replication

Player inventory state is replicated.

Server owns modifications.

---

# Future Expansion

- Trading
- Crafting
- Storage Containers
- Currency Systems
