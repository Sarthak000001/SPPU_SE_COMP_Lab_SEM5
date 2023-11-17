//SJF Pre-emptive
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
    int remainingT;
    Process(char pN, int at, int bt)
    {
        this->pN = pN;
        this->arrivalT = at;
        this->burstT = bt;
        this->completionT = -1;
        this->turnAroundT = -1;
        this->waitingT = -1;
        this->remainingT = bt;
    }

    bool operator<(const Process &other) const
    {
        return remainingT > other.remainingT;
    }
};

class SJF
{
public:
    vector<Process> processes;
    void input(int n){
        for(int i=0; i<n; i++){
            char pn;
            int at, bt, p;
            cout<<"ProcessNo : ";
            cin>>pn;
            cout<<"Arival Time : ";
            cin>>at;
            cout<<"Burst Time : ";
            cin>>bt;
            cout<<endl;
            Process pr(pn, at, bt);
            processes.push_back(pr);
        }
    }
    void completionTime()
    {
        sort(processes.begin(),processes.end(),[](Process &a,Process &b){
            return a.arrivalT < b.arrivalT;
        });
        vector<Process>temp;//to store the temporarily completed processes
        priority_queue<Process>q;//maintain processes that are ready to execute
        int currentT = 0;//keep track of current time
        while(!q.empty() || !processes.empty()){
            
            while(!processes.empty()&&processes.front().arrivalT<=currentT){
                q.push(processes.front());
                processes.erase(processes.begin());
            }
            if(!q.empty()){
                //execute the process with shortest burst time
                Process tempP = q.top();
                q.pop();

                currentT++;
                tempP.remainingT--;
                //if process doesn't complete,it's pushed back into the queue
                if(tempP.remainingT > 0){
                    q.push(tempP);
                }else{
                    //process executed completely
                    tempP.completionT = currentT;
                    temp.push_back(tempP);
                }
            }
            else{
                currentT++;
            }
        }
        processes = temp;
    }
    void turnAroundTime(){
        for(int i=0;i < processes.size();i++){
            processes[i].turnAroundT=processes[i].completionT - processes[i].arrivalT;
        }
    }
    void waitingTime(){
        for(int i=0;i < processes.size();i++){
            processes[i].waitingT = processes[i].turnAroundT - processes[i].burstT;
        }
    }
    void execute(){
        completionTime();
        turnAroundTime();
        waitingTime();
    }
    void display()
    {
        cout << "ProcessNO\tArrival time\tBurst time\tturnaround time\twaiting time" << endl;
        for (auto &it : processes)
        {
            cout << it.pN << "\t\t"
                 << it.arrivalT << "\t\t"
                 << it.burstT << "\t\t"
                 << it.turnAroundT << "\t\t"
                 << it.waitingT << "\t\t"
                 << endl;
        }
    }
};

int main()
{
    SJF sjf;
    sjf.input(5);
    sjf.execute();
    sjf.display();
    return 0;
}