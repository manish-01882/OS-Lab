#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Process {
    int pid;        // Process ID
    int arrival;    // Arrival Time
    int burst;      // Burst Time
};

bool compareArrival(const Process &a, const Process &b) {
    return a.arrival < b.arrival;
}

bool compareBurst(const Process &a, const Process &b) {
    return a.burst < b.burst;
}

void sjf(vector<Process> &processes) {
    sort(processes.begin(), processes.end(), compareArrival); // Sort processes by arrival time
    int n = processes.size();
    int currentTime = 0;
    int totalWaitingTime = 0;
    int totalTurnaroundTime = 0;

    cout << "Process ID\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n";

    for (int i = 0; i < n; i++) {
        currentTime += processes[i].burst;
        totalWaitingTime += currentTime - processes[i].arrival - processes[i].burst;
        totalTurnaroundTime += currentTime - processes[i].arrival;
        cout << processes[i].pid << "\t\t" << processes[i].arrival << "\t\t" << processes[i].burst << "\t\t"
             << currentTime - processes[i].arrival - processes[i].burst << "\t\t" << currentTime - processes[i].arrival << "\n";
    }

    // Calculate average waiting time and average turnaround time
    float avgWaitingTime = (float) totalWaitingTime / n;
    float avgTurnaroundTime = (float) totalTurnaroundTime / n;

    cout << "\nAverage Waiting Time: " << avgWaitingTime << endl;
    cout << "Average Turnaround Time: " << avgTurnaroundTime << endl;
}

int main() {
    vector<Process> processes = {
        {1, 0, 6},
        {2, 1, 8},
        {3, 2, 7},
        {4, 3, 3},
        {5, 4, 4}
    };

    sjf(processes);

    return 0;
}
