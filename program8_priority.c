#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

typedef struct {
    int process_id;
    int arrival_time;
    int burst_time;
    int priority;
    int waiting_time;
    int turnaround_time;
    int completion_time;
    bool completed;
} Process;

void priority_scheduling(Process processes[], int n) {
    int current_time = 0;
    int completed_processes = 0;

    while (completed_processes < n) {
        int highest_priority_idx = -1;
        int min_priority = INT_MAX;

        // Find the highest priority job among available processes
        for (int i = 0; i < n; i++) {
            if (!processes[i].completed && processes[i].arrival_time <= current_time) {
                if (processes[i].priority < min_priority) {
                    min_priority = processes[i].priority;
                    highest_priority_idx = i;
                }
            }
        }

        if (highest_priority_idx == -1) {
            current_time++; // CPU is idle
        } else {
            Process *p = &processes[highest_priority_idx];
            p->waiting_time = current_time - p->arrival_time;
            p->completion_time = current_time + p->burst_time;
            p->turnaround_time = p->completion_time - p->arrival_time;
            p->completed = true;
            current_time = p->completion_time;
            completed_processes++;
        }
    }
}

void display_results(Process processes[], int n) {
    float total_waiting = 0, total_turnaround = 0;

    printf("\n--- Priority Scheduling Results (Non-Preemptive) ---\n");
    printf("PID\tArrival\tBurst\tPriority\tWaiting\tTurnaround\tCompletion\n");
    printf("-------------------------------------------------------------------\n");

    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t\t%d\t%d\t\t%d\n",
               processes[i].process_id,
               processes[i].arrival_time,
               processes[i].burst_time,
               processes[i].priority,
               processes[i].waiting_time,
               processes[i].turnaround_time,
               processes[i].completion_time);

        total_waiting += processes[i].waiting_time;
        total_turnaround += processes[i].turnaround_time;
    }

    printf("-------------------------------------------------------------------\n");
    printf("Average Waiting Time: %.2f\n", total_waiting / n);
    printf("Average Turnaround Time: %.2f\n", total_turnaround / n);
}

int main() {
    int n;
    printf("=== Priority Scheduling (Non-Preemptive) ===\n");
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
        printf("Priority: ");
        scanf("%d", &processes[i].priority);
        processes[i].completed = false;
    }

    priority_scheduling(processes, n);
    display_results(processes, n);

    free(processes);
    return 0;
}
