#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

void sstf_disk_scheduling(int requests[], int n, int head) {
    int total_movement = 0;
    int serviced[n];
    for (int i = 0; i < n; i++)
        serviced[i] = 0;

    printf("\n--- SSTF Disk Scheduling ---\n");
    printf("Head movement sequence:\n%d", head);

    for (int i = 0; i < n; i++) {
        int min_dist = INT_MAX;
        int next_req_idx = -1;

        // Find the closest unserviced request
        for (int j = 0; j < n; j++) {
            if (!serviced[j]) {
                int dist = abs(requests[j] - head);
                if (dist < min_dist) {
                    min_dist = dist;
                    next_req_idx = j;
                }
            }
        }

        total_movement += min_dist;
        head = requests[next_req_idx];
        serviced[next_req_idx] = 1;

        printf(" -> %d", head);
    }

    printf("\n\nTotal head movement: %d cylinders\n", total_movement);
}

int main() {
    int requests[] = {98, 183, 37, 122, 14, 124, 65, 67};
    int n = sizeof(requests) / sizeof(requests[0]);
    int initial_head = 53;

    printf("=== SSTF Disk Scheduling Algorithm ===\n");
    printf("Request Queue: 98, 183, 37, 122, 14, 124, 65, 67\n");
    printf("Initial Head Position: %d\n", initial_head);

    sstf_disk_scheduling(requests, n, initial_head);

    return 0;
}
