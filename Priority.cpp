#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Process {
    int pid;
    int arrival_time;
    int burst_time;
    int priority;
    int completion_time;
    int waiting_time;
    int turnaround_time;
};

bool compareArrivalTime(Process p1, Process p2) {
    return p1.arrival_time < p2.arrival_time;
}

bool comparePriority(Process p1, Process p2) {
    if (p1.priority == p2.priority) {
        return p1.arrival_time < p2.arrival_time;
    }
    return p1.priority > p2.priority;
}

int main() {
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;

    vector<Process> processes(n);

    for (int i = 0; i < n; ++i) {
        cout << "Enter arrival time, burst time, and priority for process " << i + 1 << ": ";
        cin >> processes[i].arrival_time >> processes[i].burst_time >> processes[i].priority;
        processes[i].pid = i + 1;
    }

    sort(processes.begin(), processes.end(), compareArrivalTime);

    int current_time = 0;
    double total_waiting_time = 0, total_turnaround_time = 0;

    while (!processes.empty()) {
        vector<Process>::iterator current_process = processes.end();
        for (auto it = processes.begin(); it != processes.end(); ++it) {
            if (it->arrival_time <= current_time) {
                if (current_process == processes.end() || comparePriority(*it, *current_process)) {
                    current_process = it;
                }
            }
        }

        if (current_process == processes.end()) {
            current_time += 1;
            continue;
        }

        current_time += current_process->burst_time;
        current_process->completion_time = current_time;
        current_process->turnaround_time = current_process->completion_time - current_process->arrival_time;
        current_process->waiting_time = current_process->turnaround_time - current_process->burst_time;

        total_waiting_time += current_process->waiting_time;
        total_turnaround_time += current_process->turnaround_time;

        cout << "\n\nPID\tAT\tBT\tPR\tCT\tTAT\tWT" << endl;
        cout << current_process->pid << "\t" << current_process->arrival_time << "\t" << current_process->burst_time << "\t" << current_process->priority << "\t" << current_process->completion_time << "\t" << current_process->turnaround_time << "\t" << current_process->waiting_time << endl;

        processes.erase(current_process);
    }

    cout << "\nAverage waiting time: " << total_waiting_time / n << endl;
    cout << "Average turnaround time: " << total_turnaround_time / n << endl<<endl;

    return 0;
}
