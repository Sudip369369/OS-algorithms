#include <stdio.h>
#include <stdbool.h>

#define MAX_P 10
#define MAX_R 10

void calculate_need(int need[MAX_P][MAX_R], int max[MAX_P][MAX_R],
                    int allocation[MAX_P][MAX_R], int p, int r) {
    for (int i = 0; i < p; i++)
        for (int j = 0; j < r; j++)
            need[i][j] = max[i][j] - allocation[i][j];
}

bool is_safe(int processes[], int available[], int max[][MAX_R],
             int allocation[][MAX_R], int p, int r) {
    int need[MAX_P][MAX_R];
    calculate_need(need, max, allocation, p, r);

    bool finish[MAX_P] = {0};
    int safe_seq[MAX_P];
    int work[MAX_R];

    for (int i = 0; i < r; i++)
        work[i] = available[i];

    int count = 0;
    while (count < p) {
        bool found = false;
        for (int proc = 0; proc < p; proc++) {
            if (!finish[proc]) {
                int j;
                for (j = 0; j < r; j++)
                    if (need[proc][j] > work[j])
                        break;
                if (j == r) {
                    for (int k = 0; k < r; k++)
                        work[k] += allocation[proc][k];
                    safe_seq[count++] = proc;
                    finish[proc] = true;
                    found = true;
                }
            }
        }
        if (!found) {
            printf("\nSystem is not in a safe state.\n");
            return false;
        }
    }

    printf("\nSystem is in a safe state.\nSafe sequence is: ");
    for (int i = 0; i < p; i++)
        printf("P%d ", safe_seq[i]);
    printf("\n");
    return true;
}

int main() {
    int p = 5, r = 3;
    int processes[] = {0, 1, 2, 3, 4};
    int available[] = {3, 3, 2};
    int max[MAX_P][MAX_R] = {
        {7, 5, 3},
        {3, 2, 2},
        {9, 0, 2},
        {2, 2, 2},
        {4, 3, 3}
    };
    int allocation[MAX_P][MAX_R] = {
        {0, 1, 0},
        {2, 0, 0},
        {3, 0, 2},
        {2, 1, 1},
        {0, 0, 2}
    };

    printf("=== Banker's Algorithm for Deadlock Avoidance ===\n");
    printf("Initial System State:\n");
    printf("Processes: %d, Resources: %d\n", p, r);
    printf("Available Resources: 3 3 2\n");

    printf("\nAllocation Matrix:\n");
    for (int i = 0; i < p; i++) {
        for (int j = 0; j < r; j++)
            printf("%d ", allocation[i][j]);
        printf("\n");
    }

    printf("\nMax Matrix:\n");
    for (int i = 0; i < p; i++) {
        for (int j = 0; j < r; j++)
            printf("%d ", max[i][j]);
        printf("\n");
    }

    is_safe(processes, available, max, allocation, p, r);

    return 0;
}
