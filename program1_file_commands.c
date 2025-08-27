#include <stdio.h>
#include <stdlib.h>

// Compare function for qsort
int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

void scan_disk_scheduling(int requests[], int n, int head, int disk_size, int direction) {
    int total_movement = 0;
    int current_head = head;

    // Sort requests
    qsort(requests, n, sizeof(int), compare);

    printf("\n--- SCAN (Elevator) Disk Scheduling ---\n");
    printf("Head movement sequence:\n%d", head);

    if (direction == 1) { // Moving towards higher tracks
        // Service requests in the current direction
        for (int i = 0; i < n; i++) {
            if (requests[i] >= current_head) {
                total_movement += abs(requests[i] - current_head);
                current_head = requests[i];
                printf(" -> %d", current_head);
            }
        }
        // Move to the end of the disk
        total_movement += abs(disk_size - 1 - current_head);
        current_head = disk_size - 1;
        printf(" -> %d", current_head);

        // Service requests in the reverse direction
        for (int i = n - 1; i >= 0; i--) {
            if (requests[i] < head) {
                total_movement += abs(requests[i] - current_head);
                current_head = requests[i];
                printf(" -> %d", current_head);
            }
        }
    } else { // Moving towards lower tracks
        // Service requests in the current direction
        for (int i = n - 1; i >= 0; i--) {
            if (requests[i] <= current_head) {
                total_movement += abs(requests[i] - current_head);
                current_head = requests[i];
                printf(" -> %d", current_head);
            }
        }
        // Move to start of the disk
        total_movement += current_head; // from current_head to 0
        current_head = 0;
        printf(" -> %d", current_head);

        // Service remaining requests in the reverse direction
        for (int i = 0; i < n; i++) {
            if (requests[i] > head) {
                total_movement += abs(requests[i] - current_head);
                current_head = requests[i];
                printf(" -> %d", current_head);
            }
        }
    }

    printf("\n\nTotal head movement: %d cylinders\n", total_movement);
}

int main() {
    int requests[] = {98, 183, 37, 122, 14, 124, 65, 67};
    int n = sizeof(requests) / sizeof(requests[0]);
    int initial_head = 53;
    int disk_size = 200;
    int direction = 1; // 1 for high, -1 for low

    printf("=== SCAN Disk Scheduling Algorithm ===\n");
    printf("Request Queue: 98, 183, 37, 122, 14, 124, 65, 67\n");
    printf("Initial Head: %d, Disk Size: %d, Direction: Towards High\n", initial_head, disk_size);

    scan_disk_scheduling(requests, n, initial_head, disk_size, direction);

    return 0;
}
