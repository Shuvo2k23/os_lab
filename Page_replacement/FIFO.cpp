#include <iostream>
#include <vector>
using namespace std;

void FIFO() {
    vector<int> pages = {7, 0, 1, 2, 0, 3, 0, 4};
    int capacity = 3;

    vector<int> frame;
    int pageFaults = 0;
    int index = 0;

    for (int i = 0; i < pages.size(); i++) {
        bool found = false;

        for (int j = 0; j < frame.size(); j++) {
            if (frame[j] == pages[i]) {
                found = true;
                break;
            }
        }

        if (!found) {
            if (frame.size() < capacity) {
                frame.push_back(pages[i]);
            } else {
                frame[index] = pages[i];
                index = (index + 1) % capacity;
            }
            pageFaults++;
        }
    }

    cout << "FIFO Page Faults: " << pageFaults << endl;
}

int main() {
    FIFO();
    return 0;
}