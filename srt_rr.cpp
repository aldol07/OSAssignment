#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

struct Process {
    int id, arrival, burst, remaining;
    Process(int i, int a, int b) : id(i), arrival(a), burst(b), remaining(b) {}
};

void SRTF(vector<Process>& processes) {
    int n = processes.size();
    int time = 0, completed = 0;
    vector<Process> readyQueue;

    while (completed < n) {
        readyQueue.clear();
        for (auto& p : processes) {
            if (p.arrival <= time && p.remaining > 0) {
                readyQueue.push_back(p);
            }
        }

        if (!readyQueue.empty()) {
            auto shortest = min_element(readyQueue.begin(), readyQueue.end(), 
                [](const Process& a, const Process& b) {
                    return a.remaining < b.remaining;
                });

            Process& current = *shortest;
            current.remaining--;
            if (current.remaining == 0) {
                completed++;
                cout << "Process " << current.id << " completed at time " << time + 1 << endl;
            }
        }
        time++;
    }
}

void RR(vector<Process>& processes, int quantum) {
    int n = processes.size();
    int time = 0;
    queue<Process*> readyQueue;
    vector<Process*> processMap(n);

    for (int i = 0; i < n; ++i) {
        processMap[i] = &processes[i];
    }

    while (true) {
        bool done = true;

        for (auto& p : processMap) {
            if (p->remaining > 0) {
                done = false;
                if (p->arrival <= time) {
                    readyQueue.push(p);
                }
            }
        }

        if (done) break;

        if (!readyQueue.empty()) {
            Process* current = readyQueue.front();
            readyQueue.pop();
            int burstTime = min(current->remaining, quantum);
            current->remaining -= burstTime;
            time += burstTime;

            if (current->remaining > 0) {
                current->arrival = time;
                readyQueue.push(current);
            } else {
                cout << "Process " << current->id << " completed at time " << time << endl;
            }
        } else {
            time++;
        }
    }
}

int main() {
    int n, choice;
    cout << "Enter the number of processes: ";
    cin >> n;

    vector<Process> processes;
    for (int i = 0; i < n; ++i) {
        int arrival, burst;
        cout << "Enter arrival time and burst time for process " << i + 1 << ": ";
        cin >> arrival >> burst;
        processes.emplace_back(i + 1, arrival, burst);
    }

    cout << "Choose scheduling algorithm:\n1. SRTF\n2. Round Robin\nEnter choice (1 or 2): ";
    cin >> choice;

    if (choice == 1) {
        SRTF(processes);
    } else if (choice == 2) {
        int quantum;
        cout << "Enter time quantum for Round Robin: ";
        cin >> quantum;
        RR(processes, quantum);
    } else {
        cout << "Invalid choice.\n";
    }

    return 0;
}
