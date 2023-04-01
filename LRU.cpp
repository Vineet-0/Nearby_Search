#include <iostream>
#include <vector>
#include <unordered_map>
#include <list>

using namespace std;

int page_faults(int num_frames, const vector<int> &pages) {
    unordered_map<int, list<int>::iterator> frames;
    list<int> lru_list;
    int page_fault_count = 0;

    for (int page : pages) {
        if (frames.size() < num_frames) {
            if (frames.find(page) == frames.end()) {
                lru_list.push_front(page);
                frames[page] = lru_list.begin();
                page_fault_count++;
            } else {
                lru_list.erase(frames[page]);
                lru_list.push_front(page);
                frames[page] = lru_list.begin();
            }
        } else {
            if (frames.find(page) == frames.end()) {
                int victim_page = lru_list.back();
                lru_list.pop_back();
                frames.erase(victim_page);
                lru_list.push_front(page);
                frames[page] = lru_list.begin();
                page_fault_count++;
            } else {
                lru_list.erase(frames[page]);
                lru_list.push_front(page);
                frames[page] = lru_list.begin();
            }
        }
    }

    return page_fault_count;
}

int main() {
    vector<int> pages = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2, 1, 2, 0, 1, 7, 0, 1};
    int num_frames = 3;

    int faults = page_faults(num_frames, pages);
    cout << "\n\nNumber of page faults: " << faults << endl<<endl;

    return 0;
}
