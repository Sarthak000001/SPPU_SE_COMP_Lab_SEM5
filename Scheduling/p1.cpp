#include <bits/stdc++.h>
using namespace std;

class Process{
    public:
    char pn; //process no
    int arrival_time;
    int burst_time;
    int completion_time;
    int turn_around_time;
    int waiting_time;
    Process(char pn,int at,int bt){
        this->pn = pn;
        this->arrival_time = at;
        this->burst_time = bt;
        this->completion_time = -1;
        this->turn_around_time = -1;
        this->waiting_time = -1;
    }
};

class SJF{
    public:
    vector<Process>processes;
    void completionTime(){
        
    }
};
int main(){

    return 0;
}