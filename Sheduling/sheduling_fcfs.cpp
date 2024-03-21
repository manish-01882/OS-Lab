#include<iostream>
#include<vector>
using namespace std;

void findWaitTime(vector<int> &processes, int &n, vector<int> &bt, vector<int> &wt){
    wt.push_back(0);
    for (int i=0; i<n; ++i){
        wt[i] = bt[i-1] + wt[i-1];
    }
}

void findTurnAroundTime( vector<int> &processes, int &n,vector<int> &bt, vector<int> &wt, vector<int> &total){
    for(int i=1; i<n; ++i){
        total.push_back(bt[i-1] + wt[i-1]);
    }
}

void findAvgTime(vector<int> &processes, int &n, vector<int> &bt){
    vector<int> wt, total;
    int total_wt = 0, total_total = 0;
    findWaitTime(processes, n, bt, wt);
    findTurnAroundTime(processes, n , bt, wt, total);
    cout << "Processes "<< " Burst time  "
        << " Waiting time  " << " Turn around time"<<endl;

    for(int i=0; i<n; ++i){
        total_wt = total_wt + wt[i];
        total_total = total_total + total[i];
        cout << "   " << i+1 << "\t\t" << bt[i] << "\t      "
            << wt[i] << "\t\t   " << total[i] <<endl;
    }
       cout << "Average waiting time = "
         << (float)total_wt / (float)n;
    cout << "\nAverage turn around time = "
         << (float)total_total / (float)n;
}

int main(){
    vector<int> processes = {1,2,3};
    int n = processes.size();
    vector<int> burst_time = {10,5,8};
    findAvgTime(processes, n, burst_time);
    cout << endl;
    return 0;
}