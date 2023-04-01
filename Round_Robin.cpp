#include <iostream>
#include <vector>
#include <queue>

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

    int time_quantum;
    cout << "Enter the time quantum: ";
    cin >> time_quantum;

    queue<Process *> ready_queue;
    int current_time = 0;
    int completed_processes = 0;
    double total_waiting_time = 0, total_turnaround_time = 0;

    while (completed_processes < n) {
        for (Process &p : processes) {
            if (p.arrival_time == current_time && p.remaining_time > 0) {
                ready_queue.push(&p);
            }
        }

        if (!ready_queue.empty()) {
            Process *current_process = ready_queue.front();
            ready_queue.pop();

            if (current_process->remaining_time > time_quantum) {
                current_process->remaining_time -= time_quantum;
                current_time += time_quantum;
            } else {
                current_time += current_process->remaining_time;
                current_process->remaining_time = 0;
                current_process->completion_time = current_time;
                current_process->turnaround_time = current_process->completion_time - current_process->arrival_time;
                current_process->waiting_time = current_process->turnaround_time - current_process->burst_time;

                total_waiting_time += current_process->waiting_time;
                total_turnaround_time += current_process->turnaround_time;
                completed_processes++;
            }

            for (Process &p : processes) {
                if (p.arrival_time > current_process->arrival_time && p.arrival_time <= current_time && p.remaining_time > 0) {
                    ready_queue.push(&p);
                }
            }

            if (current_process->remaining_time > 0) {
                ready_queue.push(current_process);
            }
        } else {
            current_time++;
        }
    }

    cout << "\n\nPID\tAT\tBT\tCT\tTAT\tWT" << endl;
    for (const auto &p : processes) {
        cout << p.pid << "\t" << p.arrival_time << "\t" << p.burst_time << "\t" << p.completion_time << "\t" << p.turnaround_time << "\t" << p.waiting_time << endl;
    }

    cout << "\nAverage waiting time: " << total_waiting_time / n << endl;
    cout << "Average turnaround time: " << total_turnaround_time / n << endl <<endl;

    return 0;
}
