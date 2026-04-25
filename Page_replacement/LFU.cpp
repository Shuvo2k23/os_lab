#include <iostream>
#include <vector>
using namespace std;

void LFU() {
    vector<int> pages = {5, 0, 1, 3, 2, 4, 1, 0, 5};
    int capacity = 4;

    vector<int> frame(capacity, -1);
    vector<int> freq(capacity, 0);
    vector<int> loadedAt(capacity, -1);

    int pageFaults = 0;

    for (int i = 0; i < (int)pages.size(); i++) {
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
            int pos = -1;

            // Fill any empty frame first.
            for (int j = 0; j < capacity; j++) {
                if (frame[j] == -1) {
                    pos = j;
                    break;
                }
            }

            // If all frames are full, evict LFU page.
            // Tie-breaker: evict the page that was loaded earliest.
            if (pos == -1) {
                int minFreq = freq[0];
                pos = 0;
                for (int j = 1; j < capacity; j++) {
                    if (freq[j] < minFreq) {
                        minFreq = freq[j];
                        pos = j;
                    } else if (freq[j] == minFreq && loadedAt[j] < loadedAt[pos]) {
                        pos = j;
                    }
                }
            }

            frame[pos] = pages[i];
            freq[pos] = 1;
            loadedAt[pos] = i;
            pageFaults++;
        }
    }

    cout << "LFU Page Faults: " << pageFaults << endl;
}

int main() {
    LFU();
    return 0;
}