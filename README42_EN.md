*This project has been created as part of the 42 curriculum by alebaron.*

# Codexion: Master the Race for Resources Before the Deadline

## Description

Codexion is a C programming project exploring the challenges of concurrency and resource synchronization.

The project simulates a place where developers (threads) compete for access to limited resources (USB dongles protected by mutexes) to compile their code. The objective is to implement a robust scheduling algorithm (FIFO or EDF) capable of preventing deadlocks, managing hardware cooldown times, and preventing developer "burnout" before the fixed deadline.

### Key points of the project:

- **Multi-threading**: Management of complex life cycles (compile, debug, refactor) via pthread.
- **Custom scheduling**: Implementation of a priority queue (Heap) for First In, First Out (fifo) and Earliest Deadline First (edf).
- **Fine synchronization**: Use of condition variables and mutexes to orchestrate access to shared dongles without deadlock.
- **Real-time monitoring**: Simulation monitoring by a dedicated thread for precise burnout detection to within 10ms.

## Installation

```bash
# Clone the project
git clone https://github.com/alizealebaron/codexion.git
cd codexion

# Compile the project
make
```

### Makefile Commands

```bash
# Run the program with default parameters
make run

# Clean object files
make clean

# Clean object files and executable
make fclean

# Recompile all files
make re

# Similar to make
make all
```

### Basic Execution

```bash
# Use default parameters
make run
# Pass your own parameters
./codexion <number_of_coders> <time_to_burnout> <time_to_compile> <time_to_debug> <time_to_refactor> <number_of_compiles_required> <dongle_cooldown> <scheduler>
```

## Code Architecture

### File Tree
```
codexion/
├── Makefile                  # Command automation
├── README.md                 # Project explanations in English
├── README_FR.md              # Project explanations in French
├── obj/                      # Objects after compilation
└── coders/
    ├── cleaning/          
    │   └── destroy_mutex.c   
    ├── init/
    │   ├── check_args.c
    │   └── init_struct.c
    ├── parsing/            
    │   ├── manage_dongle.c
    │   ├── manage_thread.c
    │   ├── routines_utils.c
    │   ├── routines.c
    │   ├── scheduler_utils.c
    │   ├── scheduler.c
    │   └── simulation_check.c
    ├── utils/
    │   ├── exit_utils.c
    │   ├── heap_utils.c
    │   ├── print_utils.c
    │   ├── queue_utils.c
    │   └── time_utils.c
	├── codexion.h
    └── codexion.c
```

## Challenges Encountered and Solutions

### Deadlock Prevention

The solution implements deadlock prevention. Each coder must acquire two dongles to compile, which naturally creates a deadlock risk if not handled correctly.

**Prevention Conditions:**

1. **Mutual Exclusion**: Mutexes are used to guarantee exclusive access to dongles (critical resource).

2. **Hold and Wait Eliminated**: Although technically used, the problem is solved by **fixed order of acquisition** of resources. Each coder always acquires its dongles in the same order (based on their ID). The `get_ordered_dongles()` function ensures that `first` (lower ID) is always acquired before `second` (higher ID):

```c
void	get_ordered_dongles(t_coder *coder, t_dongle **first, t_dongle **second)
{
	if (coder->left_dongle->id < coder->right_dongle->id)
	{
		*first = coder->left_dongle;
		*second = coder->right_dongle;
	}
	else
	{
		*first = coder->right_dongle;
		*second = coder->left_dongle;
	}
}
```

3. **Dual Acquisition**: Dongles are always retrieved two at a time. If either or both are not free, the coder will wait for them to become available.

4. **Circular Wait Eliminated**: Thanks to the fixed order of acquisition, there is a total ordering relationship on resources (dongles). No cycle is possible.

### Burnout Prevention

Two fair scheduling algorithms are implemented:

- **FIFO (First In, First Out)**: A coder added to the queue must wait for all coders before him to have access to dongle. The `wait_for_dongle_fifo()` function ensures that only the first element in the queue can acquire the dongles.

- **EDF (Earliest Deadline First)**: A min-priority binary heap orders coders according to `last_compile_time`. This approach favors coders who haven't compiled recently, avoiding systematic starvation.

When a coder releases the dongles, a `pthread_cond_broadcast()` wakes up all waiting threads so they can try to acquire resources according to their priority order.

### Cooldown Management

After each compilation, the dongles are updated with a cooldown time:

```c
coder->left_dongle->cooldown = time + coder->data->dongle_cooldown;
coder->right_dongle->cooldown = time + coder->data->dongle_cooldown;
```

Before acquiring a dongle, the `take_dongle()` function checks that the cooldown has elapsed. Coders trying to access a dongle in cooldown are blocked and wait for the next notification.

### Precise Burnout Detection

A dedicated monitor thread (`main_routine`) polls the state of each coder **every 100 microseconds**. It checks for each coder whether the time elapsed since the last compilation exceeds `time_to_burnout`:

```c
if (finish == 0 && (get_time() - last_compile > data->time_to_burnout))
{
	print_message(data, data->coders[i].number, LOG_BURNS_OUT);
	return (1);	// Burnout detected
}
```

This polling frequency (100 µs) allows for precise detection to approximately 10 ms, well below most burnout delays.

## Thread Synchronization Mechanisms

### Synchronization Primitives Used

The implementation uses three main primitives to orchestrate concurrency:

#### 1. **Mutex (`pthread_mutex_t`)**

- **Dongle mutex**: Each dongle has a `lock` mutex to protect its state (cooldown, is_lock).
- **Coders mutex**: Each coder has a `lock` mutex to protect its mutable data (last_compile_time, has_finished, compiles_done).
- **Print mutex**: `print_mutex` serializes all accesses to stdout.
- **Main mutex**: `main_mutex` protects the global state of the simulation (is_sim_active).
- **Queue/heap mutex**: `queue_ctrl.mutex` and `heap->mutex` protect queue structures.

#### 2. **Condition Variables (`pthread_cond_t`)**

- **Queue condition**: `queue_ctrl.cond` notifies waiting coders when a dongle is released (FIFO).
- **Heap condition**: `heap->cond` notifies waiting coders when a dongle is released (EDF).

### Coordination of Shared Resource Access

#### Dongle Access

Each dongle is protected by its own mutex. Acquisition is done in two stages with fixed order:

```c
int	take_dongle(t_coder *coder)
{
	t_dongle	*first;
	t_dongle	*second;

	get_ordered_dongles(coder, &first, &second);
	pthread_mutex_lock(&first->lock);
	if (first->cooldown <= get_time()) {
		pthread_mutex_lock(&second->lock);
		if (second->cooldown <= get_time()) {
			// Mark dongles as used
			coder->left_dongle->is_lock = 1;
			coder->right_dongle->is_lock = 1;
			pthread_mutex_unlock(&second->lock);
			pthread_mutex_unlock(&first->lock);
			return (1);	// Success
		}
		pthread_mutex_unlock(&second->lock);
	}
	pthread_mutex_unlock(&first->lock);
	return (0);	// Unable to acquire
}
```

**Race Condition Prevention**:
- Fixed order eliminates deadlocks between competing threads.
- Cooldown checks are protected by mutexes, preventing ghost reads.
- The `is_lock` state is updated atomically under protection.

#### Burnout Monitoring

The monitor uses thread-safe communication to read coder state:

```c
pthread_mutex_lock(&data->coders[i].lock);
last_compile = data->coders[i].last_compile_time;
finish = data->coders[i].has_finished;
pthread_mutex_unlock(&data->coders[i].lock);

// Check for burnout
if (finish == 0 && (get_time() - last_compile > data->time_to_burnout)) {
	// End simulation
}
```

Each coder updates `last_compile_time` in a thread-safe manner during compilation:

```c
void	compile(t_coder *coder)
{
	print_message(coder->data, coder->number, LOG_COMPILING);
	pthread_mutex_lock(&coder->lock);
	coder->last_compile_time = get_time();  // Atomic update
	pthread_mutex_unlock(&coder->lock);
	usleep(coder->data->time_to_compile * 1000);
}
```

#### Safe Simulation Shutdown

When the monitor detects burnout or complete success, it signals shutdown and wakes all threads:

```c
pthread_mutex_lock(&data->main_mutex);
data->is_sim_active = 0;  // Signal shutdown
pthread_mutex_unlock(&data->main_mutex);

// Wake all waiting threads
pthread_mutex_lock(&data->queue_ctrl.mutex);
pthread_cond_broadcast(&data->queue_ctrl.cond);
pthread_mutex_unlock(&data->queue_ctrl.mutex);

pthread_mutex_lock(&data->heap->mutex);
pthread_cond_broadcast(&data->heap->cond);
pthread_mutex_unlock(&data->heap->mutex);
```

This ensures that no thread is blocked indefinitely during shutdown.

## Resources

## The Dining Philosophers Problem

- [Philosophers 42 Guide— "The Dining Philosophers Problem"](https://medium.com/@ruinadd/philosophers-42-guide-the-dining-philosophers-problem-893a24bc0fe2)

### C Programming Tools

- [Threads, mutex and concurrent programming in C](https://www.codequoi.com/threads-mutex-et-programmation-concurrente-en-c/)
- [Heap in C](https://www.geeksforgeeks.org/c/heap-in-c/)
- [Heap in C programming made easy](https://nkugwamarkwilliam.medium.com/heap-in-c-programming-made-easy-e84a8b423660)
- [Linux manual: timeval](https://man7.org/linux/man-pages/man3/timeval.3type.html)
- [Linux manual: usleep](https://man7.org/linux/man-pages/man3/usleep.3.html)
- [Linux manual: pthread_cond](http://manpagesfr.free.fr/man/man3/pthread_cond_init.3.html)

### Codexion Visualizer

- [Visualizer by 0xS4cha and 69Nesta](https://codexion-visualizer.sacha-dev.me/)

### Other Codexion Projects

- [shadox254's project](https://github.com/shadox254/Codexion)
- [Overtekk's project](https://github.com/Overtekk/Codexion)
- [69Nesta's project](https://github.com/69Nesta/42-Codexion)

### Use of AI in this project

1. **Programming part**
   - Help with correcting certain helgrind errors
   - Help debugging certain incorrect behaviors

2. **Documentation part**
   - Spelling error correction and reformulation
   - Help with English translation

## License

This project is licensed under CC0 1.0 Universal (public domain).

---

**Last modification**: May 5, 2026
