#include <iostream>
#include <algorithm>
using namespace std;

struct Process {
    int pid;
    int arrival;
    int burst;
    int priority;
    int completion;
    int waiting;
    int turnaround;
};

// Sort by arrival time first, then by priority
bool compare(Process a, Process b) {
    if (a.arrival == b.arrival)
        return a.priority < b.priority; // smaller value = higher priority
    return a.arrival < b.arrival;
}

int main() {
    int n = 5;

    // Predefined values (no manual input)
    Process p[5] = {
        {1, 0, 5, 2},
        {2, 1, 3, 1},
        {3, 2, 8, 4},
        {4, 3, 6, 2},
        {5, 4, 2, 3}
    };

    sort(p, p + n, compare);

    int currentTime = 0;
    bool completed[5] = {false};

    int done = 0;

    while (done < n) {
        int idx = -1;
        int highestPriority = 9999;

        for (int i = 0; i < n; i++) {
            if (!completed[i] && p[i].arrival <= currentTime) {
                if (p[i].priority < highestPriority) {
                    highestPriority = p[i].priority;
                    idx = i;
                }
            }
        }

        if (idx == -1) {
            currentTime++;
        } else {
            currentTime += p[idx].burst;
            p[idx].completion = currentTime;
            p[idx].turnaround = p[idx].completion - p[idx].arrival;
            p[idx].waiting = p[idx].turnaround - p[idx].burst;

            completed[idx] = true;
            done++;
        }
    }

    // Output
    cout << "PID\tAT\tBT\tPR\tCT\tTAT\tWT\n";
    for (int i = 0; i < n; i++) {
        cout << p[i].pid << "\t"
             << p[i].arrival << "\t"
             << p[i].burst << "\t"
             << p[i].priority << "\t"
             << p[i].completion << "\t"
             << p[i].turnaround << "\t"
             << p[i].waiting << endl;
    }

    return 0;
}