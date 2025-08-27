#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int process_id;
    int arrival_time;
    int burst_time;
    int waiting_time;
    int turnaround_time;
    int completion_time;
} Process;

// Function to sort processes by arrival time
void sortByArrival(Process processes[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (processes[j].arrival_time > processes[j + 1].arrival_time) {
                Process temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }
}

void fcfs_scheduling(Process processes[], int n) {
    int current_time = 0;
    float total_waiting = 0, total_turnaround = 0;

    sortByArrival(processes, n);

    for (int i = 0; i < n; i++) {
        if (current_time < processes[i].arrival_time) {
            current_time = processes[i].arrival_time;
        }
        processes[i].waiting_time = current_time - processes[i].arrival_time;
        processes[i].completion_time = current_time + processes[i].burst_time;
        processes[i].turnaround_time = processes[i].completion_time - processes[i].arrival_time;
        current_time = processes[i].completion_time;

        total_waiting += processes[i].waiting_time;
        total_turnaround += processes[i].turnaround_time;
    }

    printf("\n--- FCFS Scheduling Results ---\n");
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
    }

    printf("-------------------------------------------------------------\n");
    printf("Average Waiting Time: %.2f\n", total_waiting / n);
    printf("Average Turnaround Time: %.2f\n", total_turnaround / n);
}

int main() {
    int n;
    printf("=== FCFS Scheduling Algorithm ===\n");
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
    }

    fcfs_scheduling(processes, n);

    free(processes);
    return 0;
}
