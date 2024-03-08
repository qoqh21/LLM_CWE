#include <stdio.h>

#define MAX_PROCESS 10

typedef struct {
    int id;
    int arrival_time;
    int burst_time;
    int remaining_time;
    int turnaround_time;
    int waiting_time;
    int completion_time;
    int is_completed;
} Process;

void round_robin(Process processes[], int n, int quantum) {
    int current_time = 0;
    int remaining_processes = n;

    while (remaining_processes > 0) {
        for (int i = 0; i < n; i++) {
            if (processes[i].is_completed)
                continue;
            
            int remaining_burst = processes[i].remaining_time;
            if (remaining_burst > quantum) {
                current_time += quantum;
                processes[i].remaining_time -= quantum;
            } else {
                current_time += remaining_burst;
                processes[i].remaining_time = 0;
                processes[i].is_completed = 1;
                processes[i].completion_time = current_time;
                remaining_processes--;
            }
        }
    }
}

void fcfs(Process processes[], int n) {
    int current_time = 0;

    for (int i = 0; i < n; i++) {
        current_time = current_time > processes[i].arrival_time ? current_time : processes[i].arrival_time;
        processes[i].waiting_time = current_time - processes[i].arrival_time;
        current_time += processes[i].burst_time;
        processes[i].turnaround_time = current_time - processes[i].arrival_time;
        processes[i].completion_time = current_time;
    }
}

void display_results(Process processes[], int n) {
    printf("Process\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");

    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\n", processes[i].id, processes[i].arrival_time,
               processes[i].burst_time, processes[i].waiting_time, processes[i].turnaround_time);
    }
}

int main() {
    Process processes[MAX_PROCESS] = {
        {1, 0, 5, 5, 0, 0, 0, 0},
        {2, 1, 3, 3, 0, 0, 0, 0},
        {3, 2, 8, 8, 0, 0, 0, 0},
        // Add more processes if needed
    };
    int n = 3; // Number of processes

    printf("Round Robin Scheduling:\n");
    round_robin(processes, n, 2);
    display_results(processes, n);

    printf("\nFirst Come First Served Scheduling:\n");
    fcfs(processes, n);
    display_results(processes, n);

    return 0;
}
