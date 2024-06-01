#include <stdio.h>

int main() {
    int n;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    int arrival_time[n], burst_time[n], waiting_time[n], turnaround_time[n];

    for (int i = 0; i < n; i++) {
        printf("Enter arrival time for process P%d: ", i + 1);
        scanf("%d", &arrival_time[i]);
        printf("Enter burst time for process P%d: ", i + 1);
        scanf("%d", &burst_time[i]);
        waiting_time[i] = 0;
        turnaround_time[i] = 0;
    }

    int remaining_time[n];
    for (int i = 0; i < n; i++) {
        remaining_time[i] = burst_time[i];
    }

    int completed = 0, time = 0;

    while (completed != n) {
        int shortest_process = -1;
        int min_remaining_time = 9999;

        for (int i = 0; i < n; i++) {
            if (arrival_time[i] <= time && remaining_time[i] < min_remaining_time && remaining_time[i] > 0) {
                shortest_process = i;
                min_remaining_time = remaining_time[i];
            }
        }

        if (shortest_process == -1) {
            time++;
        } 
        else 
        {
            remaining_time[shortest_process]--;
            if (remaining_time[shortest_process] == 0)
             {
                completed++;
                waiting_time[shortest_process] = time - arrival_time[shortest_process] - burst_time[shortest_process];
                if (waiting_time[shortest_process] < 0)
                    waiting_time[shortest_process] = 0;
                turnaround_time[shortest_process] = waiting_time[shortest_process] + burst_time[shortest_process];
            }
            time++;
        }
    }

    printf("Process\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t\t%d\t\t%d\t\t%d\n", i + 1, arrival_time[i], burst_time[i], waiting_time[i], turnaround_time[i]);
    }

    float avgWaitingTime = 0, avgTurnaroundTime = 0;
    for (int i = 0; i < n; i++) {
        avgWaitingTime += waiting_time[i];
        avgTurnaroundTime += turnaround_time[i];
    }
    avgWaitingTime /= n;
    avgTurnaroundTime /= n;

    printf("\nAverage Waiting Time: %.2f\n", avgWaitingTime);
    printf("Average Turnaround Time: %.2f\n", avgTurnaroundTime);

    return 0;
}
