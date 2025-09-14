# Philosophers

**Author:** Umut Alkan

A solution to the classic Dining Philosophers problem in C. This program simulates philosophers sitting around a table, eating, thinking, and sleeping while avoiding deadlocks and starvation.

## What is the Dining Philosophers Problem?

Imagine philosophers sitting around a circular table. Each philosopher has a fork on their left and right. To eat, a philosopher needs both forks. The challenge is to make sure no philosopher starves while avoiding deadlocks (where everyone waits forever).

## How This Solution Works

### Key Strategies

**1. Deadlock Prevention**
- Odd-numbered philosophers pick up left fork first, then right fork
- Even-numbered philosophers pick up right fork first, then left fork
- This breaks the circular waiting that causes deadlocks

**2. Fast Death Detection**
- A separate monitor thread continuously checks if any philosopher is about to die
- Uses microsecond-precision timing for quick response

**3. Thread Safety**
- All shared data is protected with mutexes
- Consistent lock ordering prevents race conditions

## How to Use

### Compilation
```bash
make
```

### Running the Program
```bash
./philo [philosophers] [time_to_die] [time_to_eat] [time_to_sleep] [optional: meal_count]
```

**Parameters:**
- `philosophers`: Number of philosophers (1-199)
- `time_to_die`: Time in milliseconds before a philosopher dies without eating
- `time_to_eat`: Time in milliseconds to eat
- `time_to_sleep`: Time in milliseconds to sleep
- `meal_count`: (Optional) Stop when each philosopher eats this many times

### Examples
```bash
# Basic simulation with 4 philosophers
./philo 4 410 200 200

# Stop when each philosopher eats 5 times
./philo 5 800 200 200 5

# Single philosopher (will die - cannot share fork with himself)
./philo 1 800 200 200
```

### Cleanup
```bash
make fclean
```

## Project Files

| File | What it does |
|------|-------------|
| `main.c` | Program entry point |
| `init.c` | Sets up philosophers and forks |
| `philo.c` | Main philosopher behavior (eat, sleep, think) |
| `monitor.c` | Watches philosophers for death |
| `time_utils.c` | Timing functions |
| `philo_utils.c` | Fork handling and status messages |

## Technical Features

- **No Deadlocks**: Mathematically guaranteed deadlock prevention
- **No Data Races**: All memory access is protected
- **Fast Response**: Death detection within 1 millisecond
- **Memory Safe**: No memory leaks or crashes
- **Scalable**: Works with 1-199 philosophers

This solution demonstrates proper concurrent programming with threads and mutexes while solving one of the classic problems in computer science.
