# Memory Management Simulation

This program simulates memory management using C++ and implements three different memory allocation algorithms: best fit, worst fit, and the Buddy algorithm.

## Introduction
The program can be compiled using the "make" command
and begins by executing `./program`, which activates processes G and M. It accepts several parameters:

- D: Total simulation duration
- lo and hi: Range for VP (Virtual Process) size in KB
- t: Inter-arrival time between VP arrivals (Poisson distribution)
- T: VP lifetime (exponentially distributed)
- S: Memory size in KB
- An integer to select the memory allocation algorithm (1 for best fit, 2 for worst fit, 3 for the Buddy algorithm)

For each execution, the results are recorded in respective log files.

## Memory Representation

The memory is represented starting from position 0 to S-1, and S must be a power of 2 for the Buddy algorithm to function correctly.

## Process Generation

- Virtual Processes (VPs) are generated based on a Poisson distribution for inter-arrival times.
- Each VP's size is randomly chosen from a uniform distribution within the range [lo, hi].
- VP lifetimes follow an exponential distribution with an average duration of T seconds.
- The simulation runs for a total duration of D seconds.

## Memory Management Algorithms

- **Best Fit and Worst Fit Algorithms:** These algorithms use a doubly linked list to manage memory. Here's how they operate:
  
  - The size of memory is determined by parameter S.
  - The memory list starts at position 0 and ends at position S-1.
  - If the list is not empty, the algorithms return the `Memory_List_Node` that precedes the memory position where the process will be placed.
  - If the list is empty, they allocate space and place the process directly in memory (returning the head of the Memory_List).
  - If there is no space, they return NULL.
  - The process occupies memory from position `x` to `x + size - 1`.
  - Gaps in memory occur between position `x' - y - 1` (the start of the next process after the gap - the end of the previous process before the gap - 1).

- **Buddy Algorithm:** The Buddy algorithm is implemented using a binary tree structure. Memory allocation and deallocation are managed through this tree.

## Communication Between G and M

- G generates VPs and notifies M about their placement in memory using "VP_Start" messages.
- G also informs M when a VP completes its execution (typically when its lifetime expires) with a "VP_Stop" message.
- Inter-process communication is facilitated through semaphores and shared memory segments.

### Simulation Termination

The simulation stops when the total simulation duration D reaches zero. Process G determines this and notifies M with a "$" message.

## Pending Processes List (L)

- A list named Pending_Processes_List, also known as L, is used to manage processes waiting to be placed in memory.
- L is implemented as a singly linked list with head/tail pointers, representing a FIFO queue.
- New processes are added to the end (tail) of the list using the `add_process` function.
- Processes are removed from the front (head) of the list using the `pop_process` function.
- Memory allocation for processes is handled externally, and memory is not released when processes are removed from this list.
- Deletion of a process occurs after its lifespan has ended and upon removal from memory (Memory_List).

## Conclusion

The simulation provides valuable insights into the efficiency of different memory allocation algorithms under various scenarios. Both the best fit and worst fit algorithms were found to be equally efficient and outperform the Buddy algorithm.


### Note

Automatic removal of processes from memory after their lifespan is not implemented for the Buddy algorithm. However, the necessary functions for deleting nodes from the tree and placing pending processes from the list into memory are implemented and functional.

### Performance Metrics

The simulation evaluates performance using the following metrics:

1. **E [Shore 1975]:** The product of time and memory, offering insights into resource utilization.

2. **Memory Gap Analysis:** Calculating the mean and variance of memory gap sizes, reflecting memory fragmentation.
