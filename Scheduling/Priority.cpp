// Prioriy Non-preemptive
#include <bits/stdc++.h>
using namespace std;

class Process
{
public:
    char pN;
    int arrivalT;
    int burstT;
    int completionT;
    int turnAroundT;
    int waitingT;
    int priority;

    Process(char pN, int at, int bt, int p)
    {
        this->pN = pN;
        this->arrivalT = at;
        this->burstT = bt;
        this->priority = p;
        this->completionT = -1;
        this->turnAroundT = -1;
        this->waitingT = -1;
    }

    // PriorityNo less -> Greater the priority
    bool operator<(const Process &other) const
    {
        return priority > other.priority;
    }
};

class PriorityScheduling
{
public:
    vector<Process> Processes;
    void inputProcesses(int n)
    {
        for (int i = 0; i < n; i++)
        {
            char pn;
            int at, bt, p;
            cout << "ProcessNo : ";
            cin >> pn;
            cout << "Priority : ";
            cin >> p;
            cout << "Arival Time : ";
            cin >> at;
            cout << "Burst Time : ";
            cin >> bt;
            cout << endl;
            Process pr(pn, at, bt, p);
            Processes.push_back(pr);
        }
    }
    void calCompletionTime()
    {

        sort(Processes.begin(), Processes.end(), [](const Process &a, const Process &b)
             { return a.arrivalT < b.arrivalT; });

        vector<Process> temp;
        priority_queue<Process> q;
        int currTime = 0;
        int i = 1;
        q.push(Processes[0]);
        while (!q.empty())
        {

            Process p = q.top();
            q.pop();

            currTime += p.burstT;
            p.completionT = currTime;
            temp.push_back(p);

            while (Processes[i].arrivalT <= currTime)
            {
                q.push(Processes[i]);
                i++;
            }
        }

        Processes = temp;
    }

    void calTurnAroundTime()
    {
        for (int i = 0; i < Processes.size(); i++)
        {
            Processes[i].turnAroundT = Processes[i].completionT - Processes[i].arrivalT;
        }
    }

    void calWaitingTime()
    {
        for (int i = 0; i < Processes.size(); i++)
        {
            Processes[i].waitingT = Processes[i].turnAroundT - Processes[i].burstT;
        }
    }

    void process()
    {
        calCompletionTime();
        calTurnAroundTime();
        calWaitingTime();
    }

    void displayProcesses()
    {
        cout << "No." << "\t" << "AT" << "\t" << "BT" << "\t" << "Prirority" << "\t" << "CT" << "\t" << "TAT" << "\t" << "WT" << endl;
        for (auto i : Processes)
        {
            cout << i.pN << "\t" << i.arrivalT << "\t" << i.burstT << "\t" << i.priority << "\t" << i.completionT << "\t" << i.turnAroundT << "\t" << i.waitingT << endl;
        }
    }

    void displayGantt()
    {
        cout << "0-" << Processes[0].completionT << ":" << Processes[0].pN << endl;
        for (int i = 1; i < Processes.size(); i++)
        {
            cout << Processes[i - 1].completionT << "-" << Processes[i].completionT << ":" << Processes[i].pN << endl;
        }
    }
};

int main()
{
    PriorityScheduling ps;
    ps.inputProcesses(7);
    ps.process();
    ps.displayProcesses();
    ps.displayGantt();
    return 0;
}