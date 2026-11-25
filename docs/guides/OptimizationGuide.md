# Optimization Guide

## Philosophy

Never optimize blindly.

Always profile first.

---

# Tools

## Unreal Insights

Primary profiling tool.

---

## Stat Commands

```text
Stat FPS

Stat Unit

Stat Game

Stat GPU
```

---

# Common Problems

## Excessive Tick Usage

Bad:

```cpp
Tick()
{
    FindEnemies();
}
```

Every frame.

---

Better:

Events

Delegates

Timers

---

# Memory Optimization

Avoid:

- Excessive Actor Spawning
- Large Textures
- Unused Components

---

# Rendering Optimization

Reduce:

- Draw Calls
- Material Complexity
- Dynamic Lights

---

# Networking Optimization

Replicate only necessary information.
