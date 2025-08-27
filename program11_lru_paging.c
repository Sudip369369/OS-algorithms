#include <stdio.h>

int find_lru(int time[], int n) {
    int min = time[0], pos = 0;
    for (int i = 1; i < n; ++i) {
        if (time[i] < min) {
            min = time[i];
            pos = i;
        }
    }
    return pos;
}

void lru_page_replacement(int pages[], int n, int capacity) {
    int frame[capacity], time[capacity];
    int counter = 0, page_faults = 0;

    for (int i = 0; i < capacity; ++i)
        frame[i] = -1;

    printf("\nReference String ->\tFrames\n");

    for (int i = 0; i < n; ++i) {
        int page = pages[i];
        int found = 0, pos = -1;

        // Check if page is already in a frame
        for (int j = 0; j < capacity; ++j) {
            if (frame[j] == page) {
                found = 1;
                counter++;
                time[j] = counter;
                break;
            }
        }

        printf("%d\t\t ->\t", page);

        if (!found) {
            page_faults++;
            int empty_frame = -1;

            // Find an empty frame
            for (int j = 0; j < capacity; j++) {
                if (frame[j] == -1) {
                    empty_frame = j;
                    break;
                }
            }

            if (empty_frame != -1) {
                pos = empty_frame;
            } else {
                pos = find_lru(time, capacity);
            }

            frame[pos] = page;
            counter++;
            time[pos] = counter;
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

    printf("=== LRU Page Replacement Algorithm ===\n");
    printf("Reference String Length: %d, Frame Capacity: %d\n", n, capacity);

    lru_page_replacement(pages, n, capacity);

    return 0;
}
