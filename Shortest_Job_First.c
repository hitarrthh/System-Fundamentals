#include <stdio.h>

int main() {
    int n;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    int processNumber[n], arrivalTime[n], burstTime[n], priority[n], waitingTime[n], turnaroundTime[n];
    int totalWaitingTime = 0, totalTurnaroundTime = 0;

    // Input details for each process
    for (int i = 0; i < n; i++) {
        processNumber[i] = i + 1;
        printf("Enter arrival time for process %d: ", i + 1);
        scanf("%d", &arrivalTime[i]);
        printf("Enter burst time for process %d: ", i + 1);
        scanf("%d", &burstTime[i]);
        printf("Enter priority for process %d: ", i + 1);
        scanf("%d", &priority[i]);
        waitingTime[i] = 0;

        turnaroundTime[i] = 0;
        
    }

    // Perform SJF Scheduling (Sort processes based on burst time)
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (burstTime[i] > burstTime[j] || (burstTime[i] == burstTime[j] && arrivalTime[i] > arrivalTime[j])) {
                // Swap processes based on burst time and arrival time
                int temp;
                temp = processNumber[i];
                processNumber[i] = processNumber[j];
                processNumber[j] = temp;
                temp = arrivalTime[i];
                arrivalTime[i] = arrivalTime[j];
                arrivalTime[j] = temp;
                temp = burstTime[i];
                burstTime[i] = burstTime[j];
                burstTime[j] = temp;
                temp = priority[i];
                priority[i] = priority[j];
                priority[j] = temp;
            }
        }
    }

    // Calculate waiting time and turnaround time
    waitingTime[0] = 0;
    turnaroundTime[0] = burstTime[0];

    for (int i = 1; i < n; i++) {
        waitingTime[i] = turnaroundTime[i - 1];
        turnaroundTime[i] = waitingTime[i] + burstTime[i];
    }

    // Calculate total waiting time and total turnaround time
    for (int i = 0; i < n; i++) {
        totalWaitingTime += waitingTime[i];
        totalTurnaroundTime += turnaroundTime[i];
    }

    // Display the table with process details, including priority
    printf("\nProcess\tArrival Time\tBurst Time\tPriority\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", processNumber[i], arrivalTime[i], burstTime[i], priority[i], waitingTime[i], turnaroundTime[i]);
    }

    // Calculate and display the average waiting time and turnaround time
    double avgWaitingTime = (double)totalWaitingTime / n;
    double avgTurnaroundTime = (double)totalTurnaroundTime / n;

    printf("\nAverage Waiting Time: %.2lf\n", avgWaitingTime);
    printf("Average Turnaround Time: %.2lf\n", avgTurnaroundTime);

    return 0;
}
