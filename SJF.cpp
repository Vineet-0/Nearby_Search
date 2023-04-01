#include<iostream>
#include<algorithm>
using namespace std;

struct Process {
    int pid;          // Process ID
    int arrivalTime;  // Arrival time of the process
    int burstTime;    // Burst time of the process
};

bool compare(Process p1, Process p2) {
    return p1.burstTime < p2.burstTime;
}

void sjf(Process p[], int n) {
    int completionTime[n];  // Array to store completion time for each process
    int waitingTime[n];     // Array to store waiting time for each process
    int turnaroundTime[n];  // Array to store turnaround time for each process
    int totalWaitingTime = 0;   // Total waiting time of all processes
    int totalTurnaroundTime = 0;   // Total turnaround time of all processes
    
    // Sort the processes by burst time
    sort(p, p+n, compare);
    
    // Calculate completion time for each process
    completionTime[0] = p[0].burstTime;
    for(int i=1; i<n; i++) {
        completionTime[i] = completionTime[i-1] + p[i].burstTime;
    }
    
    // Calculate waiting time and turnaround time for each process
    for(int i=0; i<n; i++) {
        waitingTime[i] = completionTime[i] - p[i].burstTime - p[i].arrivalTime;
        turnaroundTime[i] = completionTime[i] - p[i].arrivalTime;
        totalWaitingTime += waitingTime[i];
        totalTurnaroundTime += turnaroundTime[i];
    }
    
    // Calculate average waiting time and average turnaround time
    double avgWaitingTime = (double)totalWaitingTime / n;
    double avgTurnaroundTime = (double)totalTurnaroundTime / n;
    
    // Print the results
    cout << "\n\nPID\tArrival Time\tBurst Time\tCompletion Time\tWaiting Time\tTurnaround Time\n";
    for(int i=0; i<n; i++) {
        cout << p[i].pid << "\t" << p[i].arrivalTime << "\t\t" << p[i].burstTime << "\t\t"
             << completionTime[i] << "\t\t" << waitingTime[i] << "\t\t" << turnaroundTime[i] << "\n";
    }
    cout << "\nAverage waiting time: " << avgWaitingTime << "\n";
    cout << "Average turnaround time: " << avgTurnaroundTime << "\n\n";
}

int main() {
    Process p[4];
    
    int AT[4] = {0,1,2,3};
    int BT[4] = {8,4,9,5};
    // Input process details
    for(int i=0; i<4; i++) {
        p[i].pid = i+1;
        p[i].arrivalTime = AT[i];
        p[i].burstTime = BT[i];
    }
    // Perform SJF scheduling algorithm
    sjf(p,4);
    
    return 0;
}
