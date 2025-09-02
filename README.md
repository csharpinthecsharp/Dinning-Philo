# Dining Philosophers 🍽️

## 📖 Overview
The Dining Philosophers is a classic concurrency problem that demonstrates synchronization between multiple threads competing for shared resources.  

Imagine a group of philosophers sitting around a table. Each philosopher alternates between **thinking** and **eating**. To eat, a philosopher needs two forks — one on the left and one on the right. Since forks are shared between neighbors, synchronization is required to avoid **deadlocks** and **race conditions**.

This program simulates the philosophers’ behavior while ensuring:
- Philosophers don’t starve.
- No deadlocks occur.
- Shared resources (forks) are properly protected using mutexes.
- Logs of each philosopher’s actions are displayed with timestamps.

---

## ⚙️ Installation & Usage

### 1. Clone the repository
```bash
git clone https://github.com/csharpinthecsharp/Dinning-Philo.git
cd Dinning-Philo
```

### 2. Makefile
```bash
make
```

### 3. Run the simulation
```bash
./philosophers [number_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep] [optional:number_of_times_each_philosopher_must_eat]
```
---

## 🖥️ Example

Run a simulation with 5 philosophers:
- 800ms before dying if they don’t eat
- 200ms to eat
- 200ms to sleep
```bash
./philosophers 5 800 200 200
```🖼️ Visualization

## 🖼️ Visualization

```bash
                         (Philosopher 0)
                          THINKING
                             🍴0
                              |
                              |
        🍴4 ------------------●------------------ 🍴1
        |                 (Table)                 |
        |                                         |
 (Philosopher 4)                             (Philosopher 1)
   THINKING                                     SLEEPING
        |                                         |
        |                                         |
        🍴3 ------------------●------------------ 🍴2
                              |
                              |
                         (Philosopher 3)
                           EATING
                              |
                              |
                         (Philosopher 2)
                          THINKING

```

---

## 🧩 Notes
- Each philosopher is represented by a thread.
- Forks are protected with mutexes to avoid simultaneous access.
- A global mutex is used for clean console output.
