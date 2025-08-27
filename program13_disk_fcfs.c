#include <stdio.h>
#include <stdlib.h>

void fcfs_disk_scheduling(int requests[], int n, int head) {
    int total_movement = 0;
    printf("\n--- FCFS Disk Scheduling ---\n");
    printf("Head movement sequence:\n%d", head);

    for (int i = 0; i < n; i++) {
        total_movement += abs(requests[i] - head);
        head = requests[i];
        printf(" -> %d", head);
    }

    printf("\n\nTotal head movement: %d cylinders\n", total_movement);
}

int main() {
    int requests[] = {98, 183, 37, 122, 14, 124, 65, 67};
    int n = sizeof(requests) / sizeof(requests[0]);
    int initial_head = 53;

    printf("=== FCFS Disk Scheduling Algorithm ===\n");
    printf("Request Queue: 98, 183, 37, 122, 14, 124, 65, 67\n");
    printf("Initial Head Position: %d\n", initial_head);

    fcfs_disk_scheduling(requests, n, initial_head);

    return 0;
}
