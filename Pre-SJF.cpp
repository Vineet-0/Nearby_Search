#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Process {
    int pid;
    int arrival_time;
    int burst_time;
    int remaining_time;
    int completion_time;
    int waiting_time;
    int turnaround_time;
};

bool compareArrivalTime(Process p1, Process p2) {
    return p1.arrival_time < p2.arrival_time;
}

bool compareRemainingTime(Process p1, Process p2) {
    return p1.remaining_time < p2.remaining_time;
}

int main() {
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;

    vector<Process> processes(n);

    for (int i = 0; i < n; ++i) {
        cout << "Enter arrival time and burst time for process " << i + 1 << ": ";
        cin >> processes[i].arrival_time >> processes[i].burst_time;
        processes[i].pid = i + 1;
        processes[i].remaining_time = processes[i].burst_time;
    }

    sort(processes.begin(), processes.end(), compareArrivalTime);

    int current_time = 0;
    double total_waiting_time = 0, total_turnaround_time = 0;

    while (true) {
        int idx = -1;
        int min_remaining_time = 1e9;

        for (int i = 0; i < n; ++i) {
            if (processes[i].arrival_time <= current_time && processes[i].remaining_time < min_remaining_time && processes[i].remaining_time > 0) {
                idx = i;
                min_remaining_time = processes[i].remaining_time;
            }
        }

        if (idx == -1) break;

        processes[idx].remaining_time -= 1;
        current_time += 1;

        if (processes[idx].remaining_time == 0) {
            processes[idx].completion_time = current_time;
            processes[idx].turnaround_time = current_time - processes[idx].arrival_time;
            processes[idx].waiting_time = processes[idx].turnaround_time - processes[idx].burst_time;

            total_waiting_time += processes[idx].waiting_time;
            total_turnaround_time += processes[idx].turnaround_time;
        }
    }

    cout << "\n\nPID\tAT\tBT\tCT\tTAT\tWT" << endl;
    for (const auto &p : processes) {
        cout << p.pid << "\t" << p.arrival_time << "\t" << p.burst_time << "\t" << p.completion_time << "\t" << p.turnaround_time << "\t" << p.waiting_time << endl;
    }

    cout << "\nAverage waiting time: " << total_waiting_time / n << endl;
    cout << "Average turnaround time: " << total_turnaround_time / n << endl<<endl;

    return 0;
}
