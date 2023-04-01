#include <iostream>
#include <vector>

using namespace std;

bool is_safe_state(const vector<vector<int>> &max_claim, const vector<vector<int>> &allocated, vector<int> available) {
    int num_processes = max_claim.size();
    int num_resources = available.size();
    vector<bool> finished(num_processes, false);
    int finished_count = 0;

    while (finished_count < num_processes) {
        bool found = false;

        for (int p = 0; p < num_processes; ++p) {
            if (!finished[p]) {
                bool can_finish = true;
                for (int r = 0; r < num_resources; ++r) {
                    int remaining_need = max_claim[p][r] - allocated[p][r];
                    if (remaining_need > available[r]) {
                        can_finish = false;
                        break;
                    }
                }

                if (can_finish) {
                    for (int r = 0; r < num_resources; ++r) {
                        available[r] += allocated[p][r];
                    }
                    finished[p] = true;
                    finished_count++;
                    found = true;
                }
            }
        }

        if (!found) {
            return false;
        }
    }

    return true;
}

int main() {
    vector<vector<int>> max_claim = {
        {7, 5, 3},
        {3, 2, 2},
        {9, 0, 2},
        {2, 2, 2},
        {4, 3, 3}
    };

    vector<vector<int>> allocated = {
        {0, 1, 0},
        {2, 0, 0},
        {3, 0, 2},
        {2, 1, 1},
        {0, 0, 2}
    };

    vector<int> available = {3, 3, 2};

    bool safe = is_safe_state(max_claim, allocated, available);
    cout << "\n\nIs the system in a safe state? " << (safe ? "Yes" : "No") << endl<<endl;

    return 0;
}
