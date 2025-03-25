#include <stdio.h>
#include <limits.h>
#include <stdbool.h>

#define MAX 10

typedef struct {
    int pid;
    int arrival;
    int burst;
    int remaining;
    int start;
    int completion;
    int waiting;
    int turnaround;
    bool done;
} Process;

void fcfs(Process p[], int n) {
    int time = 0;
    for(int i = 0; i < n; i++) {
        if (time < p[i].arrival) time = p[i].arrival;
        p[i].start = time;
        time += p[i].burst;
        p[i].completion = time;
        p[i].turnaround = p[i].completion - p[i].arrival;
        p[i].waiting = p[i].turnaround - p[i].burst;
    }
}

void sjf(Process p[], int n) {
    int time = 0, completed = 0;
    while (completed < n) {
        int idx = -1, min_burst = INT_MAX;
        for (int i = 0; i < n; i++) {
            if (!p[i].done && p[i].arrival <= time && p[i].burst < min_burst) {
                min_burst = p[i].burst;
                idx = i;
            }
        }
        if (idx == -1) {
            time++;
            continue;
        }
        p[idx].start = time;
        p[idx].completion = time + p[idx].burst;
        time += p[idx].burst;
        p[idx].turnaround = p[idx].completion - p[idx].arrival;
        p[idx].waiting = p[idx].turnaround - p[idx].burst;
        p[idx].done = true;
        completed++;
    }
}

void srtf(Process p[], int n) {
    int time = 0, completed = 0, prev = -1;
    while (completed < n) {
        int idx = -1, min_remain = INT_MAX;
        for (int i = 0; i < n; i++) {
            if (p[i].arrival <= time && p[i].remaining > 0 && p[i].remaining < min_remain) {
                min_remain = p[i].remaining;
                idx = i;
            }
        }

        if (idx == -1) {
            time++;
            continue;
        }

        if (p[idx].remaining == p[idx].burst) {
            p[idx].start = time;
        }

        p[idx].remaining--;
        time++;

        if (p[idx].remaining == 0) {
            p[idx].completion = time;
            p[idx].turnaround = p[idx].completion - p[idx].arrival;
            p[idx].waiting = p[idx].turnaround - p[idx].burst;
            completed++;
        }
    }
}

void print_results(Process p[], int n, const char *title) {
    float total_wait = 0, total_turn = 0;
    printf("\n--- %s ---\n", title);
    printf("PID\tAT\tBT\tCT\tTAT\tWT\n");
    for(int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].arrival, p[i].burst,
               p[i].completion, p[i].turnaround, p[i].waiting);
        total_wait += p[i].waiting;
        total_turn += p[i].turnaround;
    }
    printf("Average Waiting Time = %.2f\n", total_wait / n);
    printf("Average Turnaround Time = %.2f\n", total_turn / n);
}

void reset(Process p[], Process copy[], int n) {
    for (int i = 0; i < n; i++) {
        p[i] = copy[i];
        p[i].remaining = p[i].burst;
        p[i].done = false;
    }
}

int main() {
    // FCFS test data
    Process fcfs_data[] = {
        {1, 0, 6}, {2, 2, 8}, {3, 4, 7}, {4, 6, 3}
    };
    int n1 = 4;

    // SJF test data
    Process sjf_data[] = {
        {1, 1, 5}, {2, 3, 2}, {3, 5, 9}, {4, 6, 4}
    };
    int n2 = 4;

    // SRTF test data
    Process srtf_data[] = {
        {1, 0, 9}, {2, 1, 4}, {3, 2, 7}, {4, 3, 2}
    };
    int n3 = 4;

    Process temp[MAX];

    // FCFS
    reset(temp, fcfs_data, n1);
    fcfs(temp, n1);
    print_results(temp, n1, "FCFS Scheduling");

    // SJF
    reset(temp, sjf_data, n2);
    sjf(temp, n2);
    print_results(temp, n2, "SJF (Non-Preemptive) Scheduling");

    // SRTF
    reset(temp, srtf_data, n3);
    srtf(temp, n3);
    print_results(temp, n3, "SRTF (Preemptive SJF) Scheduling");

    return 0;
}
