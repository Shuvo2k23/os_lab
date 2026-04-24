#include <iostream>
#include <vector>
using namespace std;

void LFU() {
    vector<int> pages = {7, 0, 1, 2, 0, 3, 0, 4};
    int capacity = 3;

    vector<int> frame(capacity, -1);
    vector<int> freq(capacity, 0);

    int pageFaults = 0;

    for (int i = 0; i < pages.size(); i++) {
        bool found = false;

        // Check if page exists
        for (int j = 0; j < capacity; j++) {
            if (frame[j] == pages[i]) {
                freq[j]++;
                found = true;
                break;
            }
        }

        if (!found) {
            int minFreq = freq[0], pos = 0;

            for (int j = 1; j < capacity; j++) {
                if (freq[j] < minFreq) {
                    minFreq = freq[j];
                    pos = j;
                }
            }

            frame[pos] = pages[i];
            freq[pos] = 1;
            pageFaults++;
        }
    }

    cout << "LFU Page Faults: " << pageFaults << endl;
}

int main() {
    LFU();
    return 0;
}