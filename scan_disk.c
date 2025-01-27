#include <stdio.h>
#define size 100

int cylinders[size];
int request;
int n;
int seektime;
int totalmoment;
int total_seek_time;
int temporary[size];

void SCAN(int cylinders[], int temporary[], int n, int request, int seektime);

void main() {
    printf("\nEnter total number of request:");
    scanf("%d", &n);

    printf("\nStart entering cylinders for disk:");
    for (int i = 0; i < n; i++) {
        scanf("%d", &cylinders[i]);
    }

    printf("\nEnter Seek time:");
    scanf("%d", &seektime);

    printf("\nEnter starting position:");
    scanf("%d", &request);

    temporary[0] = request;
    for (int i = 1; i <= n; i++) {
        temporary[i] = cylinders[i - 1];
    }

    SCAN(cylinders, temporary, n, request, seektime);

    printf("\nTOTAL movement:%d", totalmoment);
    printf("\nTOTAL seek time:%d\n", total_seek_time);


}

void SCAN(int cylinders[], int temporary[], int n, int request, int seektime) {
    int temp1, temp2, result;
    int head_position = request;
    printf("\nThe iterations:");
    for (int i = 0; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            if (temporary[i] > temporary[j]) 
            {
                int temp = temporary[i];
                temporary[i] = temporary[j];
                temporary[j] = temp;
            }
        }
    }
    int index;
    for (index = 0; index <= n; index++) {
        if (temporary[index] == head_position) {
            break;
        }
    }

    for (int i = index; i <= n; i++) {
        temp1 = temporary[i];
        temp2 = temporary[i + 1];
        result = temp1 - temp2;
        totalmoment += (result < 0) ? -result : result;
        printf("\t|%d - %d|+", temp1, temp2);
    }

    for (int i = index - 1; i >= 0; i--) {
        temp1 = temporary[i];
        temp2 = temporary[i + 1];
        result = temp1 - temp2;
        totalmoment += (result < 0) ? -result : result;
        printf("\t|%d - %d|+", temp1, temp2);
    }

    total_seek_time = totalmoment * seektime;
}
