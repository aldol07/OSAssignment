#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Process {
    int id;        
    int arrival;   
    int burst;      
    int remaining; 
    int completion; 
    int turnaround;
    int waiting;    
};
bool compareArrival(const Process &a, const Process &b) {
    return a.arrival < b.arrival;
}
void LRTF(vector<Process> &processes) {
    int n = processes.size();
    int time = 0;  
    int completed = 0; 
    int max_index = -1; 

    while (completed < n) {
        max_index = -1;
        for (int i = 0; i < n; i++) {
            if (processes[i].arrival <= time && processes[i].remaining > 0) {
                if (max_index == -1 || processes[i].remaining > processes[max_index].remaining) {
                    max_index = i;
                }
            }
        }

        if (max_index != -1) {
            processes[max_index].remaining--;
            time++;
            if (processes[max_index].remaining == 0) {
                processes[max_index].completion = time;
                processes[max_index].turnaround = processes[max_index].completion - processes[max_index].arrival;
                processes[max_index].waiting = processes[max_index].turnaround - processes[max_index].burst;
                completed++;
            }
        } else {
            time++;
        }
    }
}

int main() {
    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    vector<Process> processes(n);

    
    for (int i = 0; i < n; i++) {
        processes[i].id = i + 1;
        cout << "Enter arrival time and burst time for process " << i + 1 << ": ";
        cin >> processes[i].arrival >> processes[i].burst;
        processes[i].remaining = processes[i].burst; 
    }
    sort(processes.begin(), processes.end(), compareArrival);

    LRTF(processes);

    cout << "\nProcess\tArrival\tBurst\tCompletion\tTurnaround\tWaiting\n";
    for (const auto &p : processes) {
        cout << "P" << p.id << "\t" << p.arrival << "\t" << p.burst << "\t" 
             << p.completion << "\t\t" << p.turnaround << "\t\t" << p.waiting << endl;
    }

    return 0;
}
