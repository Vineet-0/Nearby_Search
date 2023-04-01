#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>

using namespace std;

int page_faults(int num_frames, const vector<int> &pages) {
    unordered_set<int> frames;
    int page_fault_count = 0;

    for (int i = 0; i < pages.size(); ++i) {
        int page = pages[i];

        if (frames.size() < num_frames) {
            if (frames.find(page) == frames.end()) {
                frames.insert(page);
                page_fault_count++;
            }
        } else {
            if (frames.find(page) == frames.end()) {
                int farthest_page = -1;
                int farthest_pos = -1;

                for (const auto &frame_page : frames) {
                    auto next_use = find(pages.begin() + i + 1, pages.end(), frame_page);

                    if (next_use == pages.end()) {
                        farthest_page = frame_page;
                        break;
                    } else {
                        int pos = next_use - pages.begin();
                        if (pos > farthest_pos) {
                            farthest_pos = pos;
                            farthest_page = frame_page;
                        }
                    }
                }

                frames.erase(farthest_page);
                frames.insert(page);
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
    cout << "\n\nNumber of page faults: " << faults << endl<<endl;

    return 0;
}
