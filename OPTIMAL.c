#include <stdio.h>
#include <stdbool.h>

#define MAX_FRAMES 4

int findPageIndex(int key, int framePages[], int occupiedFrames) {
    for (int i = 0; i < occupiedFrames; i++)
        if (framePages[i] == key)
            return 1;
    return 0;
}

void printFrames(int pageNumber, int framePages[], int occupiedFrames, int maxFrames) {
    printf("\n%d \t\t", pageNumber);
    for (int i = 0; i < maxFrames; i++) {
        if (i < occupiedFrames)
            printf("%d \t\t", framePages[i]);
        else
            printf("- \t\t");
    }
}

int predictOptimal(int refStr[], int framePages[], int refStrLen, int index, int occupiedFrames) {
    int result = -1, farthest = index;
    for (int i = 0; i < occupiedFrames; i++) {
        int j;
        for (j = index; j < refStrLen; j++)
         {
            if (framePages[i] == refStr[j]) 
            {
                if (j > farthest) 
                {
                    farthest = j;
                    result = i;
                }
                break;
            }
        }
        if (j == refStrLen)
            return i;
    }
    return (result == -1) ? 0 : result;
}

void optimalPageReplacement(int refStr[], int refStrLen, int maxFrames) {
    int framePages[MAX_FRAMES] = {0};
    int occupiedFrames = 0;

    printf("Stream ");
    for (int i = 0; i < maxFrames; i++)
        printf("Frame%d ", i + 1);

    int hits = 0;
    for (int i = 0; i < refStrLen; i++) {
        if (findPageIndex(refStr[i], framePages, occupiedFrames)) {
            hits++;
            printFrames(refStr[i], framePages, occupiedFrames, maxFrames);
            continue;
        }

        if (occupiedFrames < maxFrames) {
            framePages[occupiedFrames] = refStr[i];
            occupiedFrames++;
            printFrames(refStr[i], framePages, occupiedFrames, maxFrames);
        } else {
            int pos = predictOptimal(refStr, framePages, refStrLen, i + 1, occupiedFrames);
            framePages[pos] = refStr[i];
            printFrames(refStr[i], framePages, occupiedFrames, maxFrames);
        }
    }

    printf("\n\nHits: %d\n", hits);
    printf("Misses: %d", refStrLen - hits);
}

int main() {
    int refStr[] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2};
    int refStrLen = sizeof(refStr) / sizeof(refStr[0]);
    int maxFrames = MAX_FRAMES;

    printf("Optimal Page Replacement Algorithm Simulation\n");
    optimalPageReplacement(refStr, refStrLen, maxFrames);

    return 0;
}
