#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct Process {
    int pid;        // Process ID
    int arrival;    // Arrival Time
    int burst;      // Burst Time
    int remaining;  // Remaining Burst Time
};

void roundRobin(vector<Process> &processes, int quantum) {
    int n = processes.size();
    int currentTime = 0;
    int totalWaitingTime = 0;
    int totalTurnaroundTime = 0;

    queue<Process> readyQueue;

    for (int i = 0; i < n; i++) {
        processes[i].remaining = processes[i].burst;
    }

    cout << "Process ID\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n";

    int idx = 0;
    while (!readyQueue.empty() || idx < n) {
        while (idx < n && processes[idx].arrival <= currentTime) {
            readyQueue.push(processes[idx]);
            idx++;
        }

        if (readyQueue.empty()) {
            currentTime = processes[idx].arrival;
            continue;
        }

        Process currentProcess = readyQueue.front();
        readyQueue.pop();

        int executionTime = min(quantum, currentProcess.remaining);
        currentProcess.remaining -= executionTime;
        currentTime += executionTime;

        if (currentProcess.remaining > 0) {
            readyQueue.push(currentProcess);
        } else {
            int waitingTime = currentTime - currentProcess.arrival - currentProcess.burst;
            int turnaroundTime = waitingTime + currentProcess.burst;
            totalWaitingTime += waitingTime;
            totalTurnaroundTime += turnaroundTime;
            cout << currentProcess.pid << "\t\t" << currentProcess.arrival << "\t\t" << currentProcess.burst << "\t\t"
                 << waitingTime << "\t\t" << turnaroundTime << endl;
        }
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

    int quantum = 2; // Example quantum value

    roundRobin(processes, quantum);

    return 0;
}
