#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> first_fit(const vector<int> &holes, const vector<int> &processes) {
    vector<int> hole_sizes = holes;
    vector<int> allocations(processes.size(), -1);

    for (int i = 0; i < processes.size(); ++i) {
        for (int j = 0; j < hole_sizes.size(); ++j) {
            if (hole_sizes[j] >= processes[i]) {
                allocations[i] = j;
                hole_sizes[j] -= processes[i];
                break;
            }
        }
    }

    return allocations;
}

vector<int> best_fit(const vector<int> &holes, const vector<int> &processes) {
    vector<int> hole_sizes = holes;
    vector<int> allocations(processes.size(), -1);

    for (int i = 0; i < processes.size(); ++i) {
        int best_index = -1;
        int min_size_diff = INT_MAX;

        for (int j = 0; j < hole_sizes.size(); ++j) {
            int size_diff = hole_sizes[j] - processes[i];

            if (size_diff >= 0 && size_diff < min_size_diff) {
                min_size_diff = size_diff;
                best_index = j;
            }
        }

        if (best_index != -1) {
            allocations[i] = best_index;
            hole_sizes[best_index] -= processes[i];
        }
    }

    return allocations;
}

vector<int> worst_fit(const vector<int> &holes, const vector<int> &processes) {
    vector<int> hole_sizes = holes;
    vector<int> allocations(processes.size(), -1);

    for (int i = 0; i < processes.size(); ++i) {
        int worst_index = -1;
        int max_size = INT_MIN;

        for (int j = 0; j < hole_sizes.size(); ++j) {
            if (hole_sizes[j] > max_size && hole_sizes[j] >= processes[i]) {
                max_size = hole_sizes[j];
                worst_index = j;
            }
        }

        if (worst_index != -1) {
            allocations[i] = worst_index;
            hole_sizes[worst_index] -= processes[i];
        }
    }

    return allocations;
}

void print_allocations(const string &algorithm_name, const vector<int> &allocations) {
    cout << algorithm_name << ":\n";
    for (int i = 0; i < allocations.size(); ++i) {
        if (allocations[i] != -1) {
            cout << "Process " << i + 1 << " is allocated to hole " << allocations[i] + 1 << endl;
        } else {
            cout << "Process " << i + 1 << " cannot be allocated" << endl;
        }
    }
    cout << endl;
}

int main() {
    vector<int> holes = {100, 500, 200, 300, 600};
    vector<int> processes = {212, 417, 112, 426};
    cout<<endl<<endl;
    vector<int> first_fit_allocations = first_fit(holes, processes);
    print_allocations("First Fit", first_fit_allocations);

    vector<int> best_fit_allocations = best_fit(holes, processes);
    print_allocations("Best Fit", best_fit_allocations);

    vector<int> worst_fit_allocations = worst_fit(holes, processes);
    print_allocations("Worst Fit", worst_fit_allocations);

    return 0;
}
