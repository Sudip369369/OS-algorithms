# Operating Systems Algorithms in C

This repository contains **15 C programs** that implement key Operating Systems concepts. Each program is self-contained, demonstrates a specific OS algorithm, and prints step-by-step execution outputs.

## Program List

| #  | File Name                   | Description                                  |
|----|-----------------------------|----------------------------------------------|
| 1  | program1_file_commands.c    | File handling commands                       |
| 2  | program2_fork.c             | Process creation using fork                  |
| 3  | program3_pthread.c          | Multithreading using pthreads               |
| 4  | program4_pipe.c             | Inter-process communication using pipes     |
| 5  | program5_fcfs.c             | CPU Scheduling: First-Come-First-Served     |
| 6  | program6_sjf.c              | CPU Scheduling: Shortest Job First           |
| 7  | program7_rr.c               | CPU Scheduling: Round Robin                  |
| 8  | program8_priority.c         | CPU Scheduling: Priority Scheduling          |
| 9  | program9_bankers.c          | Banker's Algorithm for Deadlock Avoidance    |
| 10 | program10_fifo_paging.c     | FIFO Page Replacement                        |
| 11 | program11_lru_paging.c      | LRU Page Replacement                         |
| 12 | program12_optimal_paging.c  | Optimal Page Replacement                     |
| 13 | program13_disk_fcfs.c       | FCFS Disk Scheduling                         |
| 14 | program14_disk_sstf.c      | SSTF Disk Scheduling                         |
| 15 | program15_disk_scan.c       | SCAN (Elevator) Disk Scheduling              |

---

## How to Compile and Run

1. Clone the repository:
git clone git@github.com:Sudip369369/OS-algorithms.git
cd os-algorithms

2. Compile any program using GCC:
gcc program9_bankers.c -o bankers


3. Run the executable:
./bankers
Replace the filename with any program you want to run.

## Features
1. CPU Scheduling: FCFS, SJF, Round Robin, Priority Scheduling
2. Memory Management: FIFO, LRU, Optimal Page Replacement
3. Deadlock Avoidance: Banker's Algorithm
4. Disk Scheduling: FCFS, SSTF, SCAN
5. Process Management: fork, pthreads, pipes
6. Step-by-step output for learning purposes

## Contributing
1. Add more OS algorithms
2. Improve code readability
3. Optimize existing implementations

## License
MIT License. Use freely for educational purposes.
