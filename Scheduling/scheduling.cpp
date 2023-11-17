/*
----> Sarthak Nirgude <----
        ◉_◉
----|-----------------|----
*/
#include <bits/stdc++.h>
#define endl '\n'
using namespace std;

class Process{
    public:
    char pn;
    int at;
    int bt;
    int ct;
    int wt;
    int tat;
    int rem;
    int priority;
    Process(char pn,int at,int bt,int priority = -1){
        this->pn = pn;
        this->at = at;
        this->bt = bt;
        this->ct = this->wt = this->tat = -1;
        this->rem = bt; //sjf
        this->priority = priority;
    }
    bool operator<(const Process &other) const
    {
        if(priority == -1) return rem > other.rem; //sjf
        else return priority > other.priority; //Priority Scheduling
    }
};
class Scheduling{
  vector<Process>arr;
  int tq; //time quantum
  public:
    void input(vector<Process>temp,int tq=-1){
        //copy the i/p vector
        arr = temp;
        //sort process on basis of AT
        sort(arr.begin(),arr.end(),[](Process &a,Process &b){
            return a.at < b.at;
        });
        //for RR taking time quantum
        this->tq = (tq==-1) ? INT_MAX : tq;
    }
    //For FCFS
    void completionT_fcfs(){
        //completion time for fcfs (non-preemptive)
        arr[0].ct = arr[0].at + arr[0].bt;
        for(int i=1;i < arr.size();i++){
            arr[i].ct = max(arr[i].at,arr[i-1].ct) + arr[i].bt;
        }
    }
    //For SJF
    void completionT_sjf(){
        vector<Process>temp;//to store temporarily completed processes
        priority_queue<Process>q; //processes that are ready to execute
        int currentTime = 0; //keep track of current time 
        while(!q.empty() || !arr.empty()){

            while(!arr.empty() && arr.front().at <= currentTime){
                q.push(arr.front());
                arr.erase(arr.begin());
            }
            if(!q.empty()){
                //execute process with shortest burst time
                Process curr = q.top();
                q.pop();
                currentTime++;
                curr.rem--;
                // process doesn't complete,pushed back into the queue
                if(curr.rem > 0){
                    q.push(curr);
                }else{
                    curr.ct = currentTime;
                    temp.push_back(curr);
                }
            }else{
                currentTime++;
            }
        }
        arr = temp;
    }
    //For Priority 
    void completionT_priority(){
        vector<Process>temp;
        priority_queue<Process>q;
        int currentTime = 0;
        int i = 1;
        q.push(arr[0]);
        while(!q.empty()){
            Process curr = q.top();
            q.pop();

            currentTime += curr.bt;
            curr.ct = currentTime;
            temp.push_back(curr);

            while(arr[i].at <= currentTime){
                q.push(arr[i]);
                i++;
            }
        }
        arr = temp;
    }
    //For RR
    void completionT_RR(){
        queue<Process>q;
        vector<Process>temp;
        int currentTime = 0;
        while(!q.empty() || !arr.empty()){
            while(!arr.empty() && arr.front().at <= currentTime){
                q.push(arr.front());
                arr.erase(arr.begin());
            }
            if(!q.empty()){
                Process curr = q.front();
                q.pop();

                int executionT = min(tq, curr.rem);
                currentTime += executionT;
                curr.rem -= executionT;
                if(curr.rem > 0){
                    while(!arr.empty()&&arr.front().at<=currentTime){
                        q.push(arr.front());
                        arr.erase(arr.begin());
                    }
                    q.push(curr);//insert back the process
                }else{
                    curr.ct = currentTime;
                    temp.push_back(curr);
                }
            }else{
                currentTime++;
            }
        }
        arr = temp;
    }
    void turnAroundT(){
        for(int i=0;i < arr.size();i++){
            arr[i].tat = arr[i].ct - arr[i].at;
        }
    }
    void waitingT(){
        for(int i = 0;i < arr.size();i++){
            arr[i].wt = arr[i].tat - arr[i].bt;
        }
    }
    void display(){
        if(arr[0].priority == -1){
            cout << "ProcessNO\tArrival time\tBurst time\tCompletion time\tturnaround time\twaiting time" << endl;
            for (auto &it : arr)
            {
                cout << it.pn << "\t\t"
                    << it.at << "\t\t"
                    << it.bt << "\t\t"
                    << it.ct << "\t\t"
                    << it.tat << "\t\t"
                    << it.wt << "\t\t"
                    << endl;
            }
        }
        else{
            cout << "ProcessNO\tPriority\tArrival time\tBurst time\tCompletion time\tturnaround time\twaiting time" << endl;
            for (auto &it : arr)
            {
                cout << it.pn << "\t\t"
                    << it.priority << "\t\t"
                    << it.at << "\t\t"
                    << it.bt << "\t\t"
                    << it.ct << "\t\t"
                    << it.tat << "\t\t"
                    << it.wt << "\t\t"
                    << endl;
            }
        }

    }
};

int main()
{  
    vector<Process>arr;
    int n;
    //taking input
    cout << "Enter number of Process : ";
    cin >> n;
    for(int i=0;i < n;i++){
        char pn;int at,bt;
        cout << "Process No : ";
        cin >> pn;
        cout << "Enter AT : ";
        cin >> at;
        cout << "Enter BT : ";
        cin >> bt;
        Process p(pn,at,bt);
        arr.push_back(p);
        cout <<endl;
    }
    while(1){
        int choice;
        cout << "1.FCFS\n2.SJF\n3.Priority\n4.RR\n5.Exit" << endl;
        cout << "Enter your choice :";
        cin >> choice;
        if(choice == 1){
            // FCFS Non-preemptive 
            Scheduling fcfs;
            fcfs.input(arr);
            fcfs.completionT_fcfs();
            fcfs.turnAroundT();
            fcfs.waitingT();
            fcfs.display();
        }
        else if(choice == 2){
            // SJF preemptive 
            Scheduling sjf;
            sjf.input(arr);
            sjf.completionT_sjf();
            sjf.turnAroundT();
            sjf.waitingT();
            sjf.display();
        }
        else if(choice == 3){
            // Priority Non-preemptive
            for(int i=0;i < n;i++){
                int k;
                cout << "Enter priority for p"<<arr[i].pn<<" :";
                cin >> k;
                arr[i].priority = k;
            }
            Scheduling p;
            p.input(arr);
            p.completionT_priority();
            p.turnAroundT();
            p.waitingT();
            p.display();
        }
        else if(choice == 4){
            Scheduling rr;
            rr.input(arr,3);
            rr.completionT_RR();
            rr.turnAroundT();
            rr.waitingT();
            rr.display();
        }
        else{
            exit(0);
        }
    }
  return 0;
}