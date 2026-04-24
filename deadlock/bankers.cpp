#include <iostream>
#include <vector>
using namespace std;

// Function to find safe sequence
bool isSafe(vector<vector<int>> &alloc,
            vector<vector<int>> &max,
            vector<int> &avail,
            int n, int m) {

    vector<vector<int>> need(n, vector<int>(m));

    // Calculate Need matrix
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }

    vector<bool> finish(n, false);
    vector<int> safeSeq;

    vector<int> work = avail;

    int count = 0;

    while (count < n) {
        bool found = false;

        for (int i = 0; i < n; i++) {
            if (!finish[i]) {
                bool canExecute = true;

                for (int j = 0; j < m; j++) {
                    if (need[i][j] > work[j]) {
                        canExecute = false;
                        break;
                    }
                }

                if (canExecute) {
                    // Add allocated resources back
                    for (int j = 0; j < m; j++) {
                        work[j] += alloc[i][j];
                    }

                    safeSeq.push_back(i);
                    finish[i] = true;
                    found = true;
                    count++;
                }
            }
        }

        if (!found) {
            cout << "System is NOT in safe state!\n";
            return false;
        }
    }

    // Print safe sequence
    cout << "Safe sequence: ";
    for (int i = 0; i < n; i++) {
        cout << "P" << safeSeq[i];
        if (i != n - 1) cout << " -> ";
    }
    cout << endl;

    return true;
}

int main() {
    int n = 5; // processes
    int m = 3; // resources

    // Allocation matrix
    vector<vector<int>> alloc = {
        {0, 1, 0},
        {2, 0, 0},
        {3, 0, 2},
        {2, 1, 1},
        {0, 0, 2}
    };

    // Max matrix
    vector<vector<int>> max = {
        {7, 5, 3},
        {3, 2, 2},
        {9, 0, 2},
        {2, 2, 2},
        {4, 3, 3}
    };

    // Available resources
    vector<int> avail = {3, 3, 2};

    isSafe(alloc, max, avail, n, m);

    return 0;
}