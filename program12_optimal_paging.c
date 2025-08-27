#include <stdio.h>

int find_optimal(int pages[], int n, int frame[], int capacity, int current_idx) {
    int res = -1, farthest = current_idx;

    for (int i = 0; i < capacity; i++) {
        int j;
        for (j = current_idx; j < n; j++) {
            if (frame[i] == pages[j]) {
                if (j > farthest) {
                    farthest = j;
                    res = i;
                }
                break;
            }
        }
        if (j == n) // Page not found in future, replace it
            return i;
    }

    return (res == -1) ? 0 : res;
}

void optimal_page_replacement(int pages[], int n, int capacity) {
    int frame[capacity];
    int page_faults = 0;

    for (int i = 0; i < capacity; i++)
        frame[i] = -1;

    printf("\nReference String ->\tFrames\n");

    for (int i = 0; i < n; i++) {
        int page = pages[i];
        int found = 0;

        // Check if page is already in a frame
        for (int j = 0; j < capacity; j++) {
            if (frame[j] == page) {
                found = 1;
                break;
            }
        }

        printf("%d\t\t ->\t", page);

        if (!found) {
            page_faults++;
            int empty_frame = -1;

            // Check for empty frame
            for (int j = 0; j < capacity; j++) {
                if (frame[j] == -1) {
                    empty_frame = j;
                    break;
                }
            }

            if (empty_frame != -1) {
                frame[empty_frame] = page;
            } else {
                int pos = find_optimal(pages, n, frame, capacity, i + 1);
                frame[pos] = page;
            }
        }

        // Print current frames
        for (int j = 0; j < capacity; j++) {
            if (frame[j] != -1)
                printf("%d ", frame[j]);
        }

        if (!found)
            printf("(Page Fault)");

        printf("\n");
    }

    printf("\nTotal Page Faults: %d\n", page_faults);
}

int main() {
    int pages[] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2, 1, 2, 0, 1, 7, 0, 1};
    int n = sizeof(pages) / sizeof(pages[0]);
    int capacity = 3;

    printf("=== Optimal Page Replacement Algorithm ===\n");
    printf("Reference String Length: %d, Frame Capacity: %d\n", n, capacity);

    optimal_page_replacement(pages, n, capacity);

    return 0;
}
