#include <bits/stdc++.h>
using namespace std;

bool comp(vector<int> a, vector<int> b)
{
    if (a[1] == b[1])
    {
        if (a[2] == b[2])
            return a[0] < b[0];
        else
            return a[2] < b[2];
    }
    return a[1] > b[1];
}
bool prio(vector<int> a, vector<int> b)
{
    if (a[1] == b[1])
    {
        if (a[3] == b[3])
        {
            return a[2] < b[2];
        }
        return a[3] < b[3];
    }
    return a[1] < b[1];
}
class Scheduling
{
public:
    int n;
    vector<vector<int>> vec;

    void input()
    {
        cout << "\nEnter Number of Processes ::";
        cin >> this->n;
        vector<vector<int>> v(n);
        cout << "\nEnter ID AT BT PR of each Process :: " << endl;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                int x;
                cin >> x;
                v[i].push_back(x);
            }
        }
        this->vec = v;
    }
    void fcfs()
    {
        vector<int> ct(n);
        vector<int> tat(n);
        vector<int> wt(n);
        int x = 0;
        sort(vec.begin(), vec.end(), comp);

        // Calculating ct,tat,wt
        float avg_wt = 0.0;
        float avg_tat = 0.0;
        for (int i = 0; i < n; i++)
        {
            x += vec[i][2];
            ct[i] = x;
            tat[i] = ct[i] - vec[i][1];
            wt[i] = tat[i] - vec[i][2];
            avg_wt += wt[i];
            avg_tat += tat[i];
        }
        cout << avg_tat / n << " " << avg_wt / n << endl;
    }
    void sjf(vector<vector<int>> v)
    {
        // cout << "in sjf";
        vector<int> ans;
        int i = 0;
        int currentTime = 0;
        sort(v.begin(), v.end(), comp);

        priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>> pq;
        // //          BT      AT        ID
        pq.push({v[0][2], v[0][1], v[0][0]});
        i++;

        while (!pq.empty())
        {
            // cout << "in while";
            int id = pq.top()[2];
            int burst_time = pq.top()[0] - 1;
            int at = pq.top()[1];
            currentTime += 1;
            pq.pop();
            ans.push_back(id);
            if (burst_time != 0)
            {
                pq.push({burst_time, at, id});
            }
            while (true)
            {
                if (i < n and v[i][1] <= currentTime)
                {

                    pq.push({v[i][2], v[i][1], v[i][0]});
                    i++;
                }
                else
                    break;
            }
        }
        sort(v.begin(), v.end());
        // for (auto x : v)
        // {
        //     cout << x[0] << " " << x[1] << " " << x[2] << " " << x[3] << endl;
        // }
        vector<int> ct(n);
        for (int i = 0; i < n; i++)
        {

            ct[i] = ans.size() - (find(ans.rbegin(), ans.rend(), i + 1) - ans.rbegin());
        }
        // calc tat wt
        vector<int> tat(n);
        vector<int> wt(n);
        float avgtat = 0.0;
        float avgwt = 0.0;
        for (int i = 0; i < n; i++)
        {
            tat[i] = ct[i] - v[i][1];
            wt[i] = tat[i] - v[i][2];
            avgtat += tat[i];
            avgwt += wt[i];
        }
        cout << avgtat / n << "  " << avgwt / n << endl;
        // for (auto x : ct)
        // {
        //     cout << x << " ";
        // }
    }

    void RR(vector<vector<int>> v)
    {
        int qt;
        cout << "\nEnter Quantum Time for Round Robin Method ::";
        cin >> qt;
        int currTime = 0;
        vector<int> ans;
        int completed = 0;
        queue<vector<int>> q;
        int i = 1;
        sort(v.begin(), v.end(), comp);
        //  BT      AT        ID
        q.push({v[0][2], v[0][1], v[0][0]});
        do
        {
            int id = q.front()[2];
            int bt = q.front()[0];
            int at = q.front()[1];

            if (bt <= qt)
            {
                for (int i = 0; i < bt; i++)
                {
                    ans.push_back(id);
                }
                
                currTime += bt;
                completed++;
                while (true)
                {
                    if (i < n and v[i][1] <= currTime)
                    {

                        q.push({v[i][2], v[i][1], v[i][0]});
                        i++;
                    }
                    else
                        break;
                }
                q.pop();
            }
            else
            {
                for (int i = 0; i < qt; i++)
                {
                    ans.push_back(id);
                }
                currTime += qt;
                while (true)
                {
                    if (i < n and v[i][1] <= currTime)
                    {

                        q.push({v[i][2], v[i][1], v[i][0]});
                        i++;
                    }
                    else
                        break;
                }
                q.push({bt - qt, at, id});
                q.pop();
            }
        } while (!q.empty());
        // for (auto x : ans)
        // {
        //     cout << x << " ";
        // }
        sort(v.begin(), v.end());
        vector<int> ct(n);
        for (int i = 0; i < n; i++)
        {
            ct[i] = ans.size() - (find(ans.rbegin(), ans.rend(), i + 1) - ans.rbegin());
        }
        // calc tat wt
        vector<int> tat(n);
        vector<int> wt(n);
        float avgtat = 0.0;
        float avgwt = 0.0;
        for (int i = 0; i < n; i++)
        {
            tat[i] = ct[i] - v[i][1];
            wt[i] = tat[i] - v[i][2];
            avgtat += tat[i];
            avgwt += wt[i];
        }
        // for (auto x : wt)
        // {
        //     cout << x << " ";
        // }
        cout << avgtat / n << "  " << avgwt / n << endl;
    }
    void priority(vector<vector<int>> v)
    {
        sort(v.begin(), v.end(), prio);
        for (auto x : v)
        {
            cout << x[0] << " " << x[1] << " " << x[2] << " " << x[3] << endl;
        }
        vector<int> ct(n + 1);
        vector<int> tat(n + 1);
        vector<int> wt(n + 1);

        priority_queue<vector<int>> pq;
        pq.push({v[0][3], v[0][0], v[0][2]});
        int i = 1;
        int current_time = 0;
        // vector<int> cmp(n + 1);
        while (!pq.empty() and i <= n)
        {
            int bt = pq.top()[2];
            int id = pq.top()[1];
            // cout<<id;
            current_time += bt;
            ct[id] = current_time;
            pq.pop();
            while (true)
            {
                if (i < n and v[i][1] <= current_time)
                {
                    pq.push({v[i][3], v[i][0], v[i][2]});
                    i++;
                }
                else
                {
                    break;
                }
            }
        }
        for (auto x : ct)
        {
            cout << x << " ";
        }
        float avgtat = 0.0;
        float avgwt = 0.0;
        for (int i = 0; i < n; i++)
        {
            tat[i] = ct[i] - v[i][1];
            wt[i] = tat[i] - v[i][2];
            avgtat += tat[i];
            avgwt += wt[i];
        }
        cout << avgtat / n << "  " << avgwt / n << endl;
    }
};

int main()
{
    cout << "hey\n";
    Scheduling s;
    s.input();
    s.fcfs();
    // s.sjf(s.vec);
    // s.RR(s.vec);
    // s.priority(s.vec);

    return 0;
}