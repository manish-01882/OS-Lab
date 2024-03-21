#include <iostream>
using namespace std;

const int NUM_PROCESSES = 5;
const int NUM_RESOURCES = 3;

void calculateNeed(int need[][NUM_RESOURCES], int max[][NUM_RESOURCES], int alloc[][NUM_RESOURCES]) {
    for (int i = 0; i < NUM_PROCESSES; i++) {
        for (int j = 0; j < NUM_RESOURCES; j++) {
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }
}

bool isSafe(int processes[], int available[], int max[][NUM_RESOURCES], int alloc[][NUM_RESOURCES]) {
    int need[NUM_PROCESSES][NUM_RESOURCES];
    calculateNeed(need, max, alloc);
    bool finish[NUM_PROCESSES] = {false};

    int work[NUM_RESOURCES];
    for (int i = 0; i < NUM_RESOURCES; i++) {
        work[i] = available[i];
    }

    int safeSequence[NUM_PROCESSES];
    int count = 0;

    while (count < NUM_PROCESSES) {
        bool found = false;
        for (int i = 0; i < NUM_PROCESSES; i++) {
            if (!finish[i]) {
                bool canProcess = true;
                for (int j = 0; j < NUM_RESOURCES; j++) {
                    if (need[i][j] > work[j]) {
                        canProcess = false;
                        break;
                    }
                }
                if (canProcess) {
                    for (int j = 0; j < NUM_RESOURCES; j++) {
                        work[j] += alloc[i][j];
                    }
                    safeSequence[count++] = i;
                    finish[i] = true;
                    found = true;
                }
            }
        }
        if (!found) {
            return false; // No safe sequence found
        }
    }

    cout << "Safe sequence: ";
    for (int i = 0; i < NUM_PROCESSES - 1; i++) {
        cout << "P" << processes[safeSequence[i]] << " -> ";
    }
    cout << "P" << processes[safeSequence[NUM_PROCESSES - 1]] << endl;
    return true;
}

int main() {
    int processes[NUM_PROCESSES] = {0, 1, 2, 3, 4};
    int allocation[NUM_PROCESSES][NUM_RESOURCES] = {{0, 1, 0},
                                                     {2, 0, 0},
                                                     {3, 0, 2},
                                                     {2, 1, 1},
                                                     {0, 0, 2}};
    int max[NUM_PROCESSES][NUM_RESOURCES] = {{7, 5, 3},
                                             {3, 2, 2},
                                             {9, 0, 2},
                                             {2, 2, 2},
                                             {4, 3, 3}};
    int available[NUM_RESOURCES] = {3, 3, 2};

    if (!isSafe(processes, available, max, allocation)) {
        cout << "Unsafe state detected." << endl;
    }

    return 0;
}
