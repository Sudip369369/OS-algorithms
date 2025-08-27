#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int process_id;
    int arrival_time;
    int burst_time;
    int remaining_time;
    int waiting_time;
    int turnaround_time;
    int completion_time;
} Process;

void round_robin_scheduling(Process processes[], int n, int quantum) {
    int current_time = 0;
    int completed = 0;

    int *ready_queue = (int *)malloc(n * n * sizeof(int)); // make it large enough
    int front = 0, rear = 0;

    // Sort by arrival time
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (processes[j].arrival_time > processes[j + 1].arrival_time) {
                Process temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }

    int processed_idx = 0;
    while (processed_idx < n && processes[processed_idx].arrival_time <= current_time) {
        ready_queue[rear++] = processed_idx++;
    }

    while (completed < n) {
        if (front == rear) {
            current_time++; // CPU Idle
            while (processed_idx < n && processes[processed_idx].arrival_time <= current_time) {
                ready_queue[rear++] = processed_idx++;
            }
            continue;
        }

        int idx = ready_queue[front++];
        Process *p = &processes[idx];

        if (p->remaining_time <= quantum) {
            current_time += p->remaining_time;
            p->remaining_time = 0;
            p->completion_time = current_time;
            p->turnaround_time = p->completion_time - p->arrival_time;
            p->waiting_time = p->turnaround_time - p->burst_time;
            completed++;
        } else {
            current_time += quantum;
            p->remaining_time -= quantum;
        }

        // Add newly arrived processes
        while (processed_idx < n && processes[processed_idx].arrival_time <= current_time) {
            ready_queue[rear++] = processed_idx++;
        }

        // Add the current process back if it's not finished
        if (p->remaining_time > 0) {
            ready_queue[rear++] = idx;
        }
    }

    free(ready_queue);
}

void display_results(Process processes[], int n) {
    float total_waiting = 0, total_turnaround = 0;

    printf("\n--- Round Robin Scheduling Results (Quantum = 2) ---\n");
    printf("PID\tArrival\tBurst\tWaiting\tTurnaround\tCompletion\n");
    printf("-------------------------------------------------------------\n");

    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t\t%d\n",
               processes[i].process_id,
               processes[i].arrival_time,
               processes[i].burst_time,
               processes[i].waiting_time,
               processes[i].turnaround_time,
               processes[i].completion_time);

        total_waiting += processes[i].waiting_time;
        total_turnaround += processes[i].turnaround_time;
    }

    printf("-------------------------------------------------------------\n");
    printf("Average Waiting Time: %.2f\n", total_waiting / n);
    printf("Average Turnaround Time: %.2f\n", total_turnaround / n);
}

int main() {
    int n, quantum = 2;
    printf("=== Round Robin Scheduling Algorithm (Quantum = 2) ===\n");
    printf("Enter number of processes: ");
    scanf("%d", &n);

    Process *processes = (Process *)malloc(n * sizeof(Process));

    for (int i = 0; i < n; i++) {
        printf("\nEnter details for Process %d:\n", i + 1);
        processes[i].process_id = i + 1;
        printf("Arrival Time: ");
        scanf("%d", &processes[i].arrival_time);
        printf("Burst Time: ");
        scanf("%d", &processes[i].burst_time);
        processes[i].remaining_time = processes[i].burst_time;
    }

    round_robin_scheduling(processes, n, quantum);
    display_results(processes, n);

    free(processes);
    return 0;
}
