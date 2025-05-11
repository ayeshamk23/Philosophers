# 🧠 Philosophers – Concurrency and Synchronization

> _“The art of thinking, eating, and avoiding deadlocks.”_

---

## 📚 Project Overview

**Philosophers** is a concurrency project from **42 School**, completed on **31 July 2024**.  
It implements a simulation of the classic **Dining Philosophers Problem**, where multiple threads (philosophers) must alternate between thinking, eating, and sleeping while competing for shared resources (forks) without causing deadlocks or race conditions.

---

## 🎯 Project Objectives

- Understand and apply thread management in C
- Use mutexes to protect shared resources
- Prevent deadlocks and starvation
- Implement timing and logging for precise simulation

---

## ⚙️ Key Concepts

- 🧵 Multithreading with `pthread`
- 🔒 Mutexes for synchronization
- 🌀 Deadlock and starvation prevention
- ⏱️ Timing accuracy with `usleep` / `gettimeofday`
- 📋 Logging thread-safe actions

---

## 🛠️ How It Works

- Each philosopher is a thread
- Forks are represented using mutexes
- Philosophers must take two forks to eat
- The program must detect and handle:
  - If a philosopher dies (time to die exceeded)
  - When all have eaten enough times (optional)

---

## 💡 Concepts Learned

- Safe multithreaded programming
- Real-time logic simulation
- Shared resource management
- Clean code structuring in low-level C

---


## ✅ Evaluation Result

Here’s a screenshot of the successful evaluation (score: 100%) from the 42 intranet.
<img width="1097" alt="Screen Shot 2025-05-11 at 6 42 10 PM" src="https://github.com/user-attachments/assets/685fc9b6-eeab-4e1d-b047-d8cc5baeeb27" />

