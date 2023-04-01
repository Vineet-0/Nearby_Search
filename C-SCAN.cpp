#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>

using namespace std;

int calculate_total_head_movement(const vector<int> &requests, int initial_head_position, int max_cylinder) {
    vector<int> sorted_requests(requests);
    sorted_requests.push_back(initial_head_position);
    sorted_requests.push_back(0);
    sorted_requests.push_back(max_cylinder - 1);
    sort(sorted_requests.begin(), sorted_requests.end());

    auto it = find(sorted_requests.begin(), sorted_requests.end(), initial_head_position);
    int total_head_movement = 0;

    for (auto i = it; i != sorted_requests.end() - 1; i++) {
        total_head_movement += abs(*i - *(i + 1));
    }

    for (auto i = it - 1; i != sorted_requests.begin();) {
        total_head_movement += abs(*i - *(i - 1));
        i--;
    }

    return total_head_movement;
}

int main() {
    vector<int> requests = {98, 183, 37, 122, 14, 124, 65, 67};
    int initial_head_position = 53;
    int max_cylinder = 200;

    int total_head_movement = calculate_total_head_movement(requests, initial_head_position, max_cylinder);
    cout << "\n\nTotal head movement: " << total_head_movement << endl <<endl;

    return 0;
}
