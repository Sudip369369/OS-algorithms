#include <stdio.h>

void fifo_page_replacement(int pages[], int n, int capacity) {
    int frame[capacity];
    int frame_idx = 0;
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
            frame[frame_idx] = page;
            frame_idx = (frame_idx + 1) % capacity;
        }

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

    printf("=== FIFO Page Replacement Algorithm ===\n");
    printf("Reference String Length: %d, Frame Capacity: %d\n", n, capacity);

    fifo_page_replacement(pages, n, capacity);

    return 0;
}
