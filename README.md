# Philosophers
A project involves simulating multiple philosophers sharing limited resources, using threads and mutexes to ensure synchronization and avoid issues like deadlocks and starvation. It focuses on multithreading and concurrency.

# Explanation of keys concepts
## What Are Threads?
If we don’t use threads,
our program will do things one by one—step after step.

But when we use threads,
it’s like having friends helping you clean your house:

- One cleans the kitchen,

- One vacuums,

- You’re doing your own thing.

Everyone is doing their task at the same time!
That’s exactly what happens when you use threads:
✅ Many tasks running in parallel.

## Why Do We Use Threads?
### Speed:
Tasks happen in parallel → Program finishes faster.

### Efficiency:
Makes better use of multi-core CPUs. No wasted power!

## !! One Important Thing to Know:
Multiple threads share the same memory space.
That’s why we use something called mutex:
To make sure threads don’t step on each other’s toes
when using shared resources!

## What Is a Mutex?
A mutex (short for Mutual Exclusion) is a tool used in programming, especially in multi-threaded applications, to control access to shared resources.
The mutex lets one thread at a time
 use the resource until this thread 
is completely done with it, 
then passes it to the next thread, 
again and again, until all threads 
finish their work.
 
 ## Why Do We Need mutex?
When multiple threads work at the same time, they might access or modify the same variable or resource.
If two threads change it at the same time: Boom! Race condition. Data gets corrupted.

We use a mutex to avoid that mess by:

- Locking before accessing shared resources.

- Unlocking when done.

## Where Mutexes Work?
A mutex (mutual exclusion lock) is a synchronization tool used inside a single process.

It’s specifically used between threads within that same process.

# Explanation of some staff
### pthread_mutex_t:
is a data type in the POSIX threads library (pthread) used to represent a mutex, which is a synchronization primitive that allows threads to protect shared data from concurrent access. It is a key component in multi-threaded programming for ensuring data consistency and preventing race conditions.
### pthread_mutex_init():
function initialises the mutex referenced by mutex with attributes specified by attr. If attr is NULL, the default mutex attributes are used; the effect is the same as passing the address of a default mutex attributes object. Upon successful initialisation, the state of the mutex becomes initialised and unlocked.
### gettimeofday():
It’s a C function that grabs the current time with microsecond precision, that's why we need struct timeval because It has two fields:

     - time_t      tv_sec;   // Whole seconds since Epoch (January 1, 1970)
     - suseconds_t tv_usec;  // Microseconds (1 second = 1,000,000 microseconds) -the remaining fraction of a second
Why Use struct timeval Instead of Just time_t?
- time_t only gives seconds — not enough if you need more precise timing.

- struct timeval gives you up to microseconds → perfect for performance measuring, simulation timing, precise logs, etc.

Why Set the Second Argument to NULL (gettimeofday(&tv, NULL)?

That second argument is officially:

```c
struct timezone *tz;
```

BUT:

It’s an old feature from before modern time libraries existed.

Almost nobody uses struct timezone anymore.

It’s marked as obsolete in most systems.

That’s why you always set it to NULL now.

### pthread_create():

This function is from the POSIX Threads (pthreads) library.
Its job is:
Create a new thread that starts running a specific function.
Every philosopher must have one thread.
```c
pthread_create(&sim->philos[i].thread, NULL, &philosopher_routine, &sim->philos[i]
```
For each philosopher, I create a new thread using pthread_create. I give it the default settings, tell it to run philosopher_routine, and pass it a pointer to the philosopher’s own struct so it knows who it’s dealing with."

pthread_create returns:
- 0 if everything went okay.
- A non-zero error code if something went wrong.

Why Would pthread_create() Fail?

1️⃣ System Limit Reached.

2️⃣ Not Enough Resources.

3️⃣ Invalid Attributes (rare here since we use NULL).

4️⃣ Invalid Arguments.

### pthread_join(): 
Blocks the specified thread until other threads finish their routine.
waits for all threads that were successfully created .

### pthread_mutex_destroy():
It frees the system resources that were reserved for that mutex.

It’s like saying:

“Okay, I’m done using this lock, the program doesn’t need it anymore. Clean it up.”

Why Is It Important?
When you’re finished using mutexes (e.g., end of your program, simulation is over).

Mutexes are managed by the OS; if you don’t destroy them, you might leave behind unnecessary resources or memory usage.

That’s especially relevant if you create a lot of mutexes dynamically
