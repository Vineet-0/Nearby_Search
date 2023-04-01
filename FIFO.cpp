#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>

using namespace std;

int page_faults(int num_frames, const vector<int> &pages) {
    unordered_set<int> frames;
    queue<int> frame_queue;
    int page_fault_count = 0;

    for (int page : pages) {
        if (frames.size() < num_frames) {
            if (frames.find(page) == frames.end()) {
                frames.insert(page);
                frame_queue.push(page);
                page_fault_count++;
            }
        } else {
            if (frames.find(page) == frames.end()) {
                int victim_page = frame_queue.front();
                frame_queue.pop();
                frames.erase(victim_page);
                frames.insert(page);
                frame_queue.push(page);
                page_fault_count++;
            }
        }
    }

    return page_fault_count;
}

int main() {
    vector<int> pages = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2, 1, 2, 0, 1, 7, 0, 1};
    int num_frames = 3;

    int faults = page_faults(num_frames, pages);
    cout << "\n\nNumber of page faults: " << faults << "\n\n\n";

    return 0;
}
