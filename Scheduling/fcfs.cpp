#include <bits/stdc++.h>
using namespace std;

class Process
{
public:
    char pn; // porcessId or process no.
    int arrival_time;
    int burst_time;
    int completion_time;
    int turn_around_time;
    int waiting_time;
    Process(char pn, int at, int bt)
    {
        this->pn = pn;
        this->arrival_time = at;
        this->burst_time = bt;
        this->completion_time = -1;
        this->turn_around_time = -1;
        this->waiting_time = -1;
    }
};
class FCFS
{
public:
    vector<Process> processes;
    void input(int n)
    {
        for (int i = 0; i < n; i++)
        {
            char pn;
            int at, bt;
            cout << "Process No. : ";
            cin >> pn;
            cout << "Arrival time : ";
            cin >> at;
            cout << "Burst time : ";
            cin >> bt;
            cout << endl;
            Process p(pn, at, bt);
            processes.push_back(p);
        }
        sort(processes.begin(), processes.end(), [](Process &a, Process &b)
             { return a.arrival_time < b.arrival_time; });
    }
    void completionTime()
    {
        // Completion time is time at which the process is completed
        processes[0].completion_time = processes[0].arrival_time + processes[0].burst_time;
        for (int i = 1; i < processes.size(); i++)
        {
            if (processes[i].arrival_time > processes[i - 1].completion_time)
            {
                processes[i].completion_time = processes[i].arrival_time + processes[i].burst_time;
            }
            else
            {
                processes[i].completion_time = processes[i - 1].completion_time + processes[i].burst_time;
            }
        }
    }
    void turnAroundTime()
    {
        // Turnaround time is the time to complete the process after arrival (Ci-Ai)
        for (int i = 0; i < processes.size(); i++)
        {
            processes[i].turn_around_time = processes[i].completion_time - processes[i].arrival_time;
        }
    }
    void waitingTime()
    {
        // Waiting Time is the difference between Turn Around Time and Burst Time of a process
        for (int i = 0; i < processes.size(); i++)
        {
            processes[i].waiting_time = processes[i].turn_around_time - processes[i].burst_time;
        }
    }
    void calculate()
    {
        completionTime();
        turnAroundTime();
        waitingTime();
    }
    void ganttChart()
    {
        cout << "Gantt Chart ---> " << endl;
        cout << "0-" << processes[0].completion_time << "->" << processes[0].pn << endl;
        for (int i = 1; i < processes.size(); i++)
        {
            int maxi = max(processes[i].arrival_time, processes[i - 1].completion_time);
            cout << maxi << "-" << processes[i].completion_time << "->" << processes[i].pn << endl;
        }
    }
    void display()
    {
        cout << "ProcessNO\tArrival time\tBurst time\tturnaround time\twaiting time" << endl;
        for (auto &it : processes)
        {
            cout << it.pn << "\t\t"
                 << it.arrival_time << "\t\t"
                 << it.burst_time << "\t\t"
                 << it.turn_around_time << "\t\t"
                 << it.waiting_time << "\t\t"
                 << endl;
        }
    }
};
int main()
{
    FCFS f;
    f.input(5);
    f.calculate();
    f.display();
    f.ganttChart();
    return 0;
}