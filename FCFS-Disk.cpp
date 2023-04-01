#include <iostream>
#include <vector>
#include <cstdlib>

using namespace std;

int calculate_total_head_movement(const vector<int> &requests, int initial_head_position) {
    int total_head_movement = 0;
    int current_head_position = initial_head_position;

    for (int request : requests) {
        total_head_movement += abs(request - current_head_position);
        current_head_position = request;
    }

    return total_head_movement;
}

int main() {
    vector<int> requests = {98, 183, 37, 122, 14, 124, 65, 67};
    int initial_head_position = 53;

    int total_head_movement = calculate_total_head_movement(requests, initial_head_position);
    cout << "\n\nTotal head movement: " << total_head_movement << endl <<endl;

    return 0;
}
