#include <stdio.h>
#include <stdbool.h>

#define MAX_FRAMES 4

// Function to find the least recently used frame
int findLRU(int time[], int n) {
    int minimum = time[0], pos = 0;

    for (int i = 1; i < n; ++i) {
        if (time[i] < minimum) {
            minimum = time[i];
            pos = i;
        }
    }

    return pos;
}

// Function to simulate LRU page replacement
void lruPageReplace(int pages[], int n, int capacity) {
    int frames[capacity];
    int time[capacity];
    int pageFaults = 0;

    for (int i = 0; i < capacity; ++i) {
        frames[i] = -1;
        time[i] = -1;
    }

    for (int i = 0; i < n; ++i) {
        bool found = false;
        for (int j = 0; j < capacity; ++j) {
            if (frames[j] == pages[i]) {
                time[j] = i;
                found = true;
                break;
            }
        }

        if (!found) {
            int pos = findLRU(time, capacity);
            frames[pos] = pages[i];
            time[pos] = i;
            ++pageFaults;
        }
    }

    printf("Total Page Faults: %d\n", pageFaults);
}

int main() {
    int pages[] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2};
    int n = sizeof(pages) / sizeof(pages[0]);
    int capacity = MAX_FRAMES;

    printf("LRU Page Replacement Algorithm Simulation\n");
    lruPageReplace(pages, n, capacity);

    return 0;
}
