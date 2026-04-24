#include <iostream>
#include <vector>
using namespace std;

int findLRU(vector<int> &time, int n) {
    int min = time[0], pos = 0;

    for (int i = 1; i < n; i++) {
        if (time[i] < min) {
            min = time[i];
            pos = i;
        }
    }
    return pos;
}

void LRU() {
    vector<int> pages = {7, 0, 1, 2, 0, 3, 0, 4};
    int capacity = 3;

    vector<int> frame(capacity, -1);
    vector<int> time(capacity, 0);

    int pageFaults = 0, counter = 0;

    for (int i = 0; i < pages.size(); i++) {
        bool found = false;

        for (int j = 0; j < capacity; j++) {
            if (frame[j] == pages[i]) {
                counter++;
                time[j] = counter;
                found = true;
                break;
            }
        }

        if (!found) {
            int pos = findLRU(time, capacity);
            frame[pos] = pages[i];

            counter++;
            time[pos] = counter;
            pageFaults++;
        }
    }

    cout << "LRU Page Faults: " << pageFaults << endl;
}

int main() {
    LRU();
    return 0;
}