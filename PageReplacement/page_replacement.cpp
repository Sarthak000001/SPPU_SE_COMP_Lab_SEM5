/*
----> Sarthak Nirgude <----
        ◉_◉
----|-----------------|----
*/
#include <bits/stdc++.h>
#define endl '\n'
using namespace std;

void FIFO(int pg[], int pn, int fn)
{
    vector<int> fr(fn, -1);
    queue<int> q;
    int faults = 0, hits = 0;
    for (int i = 0; i < pn; i++)
    {
        cout << pg[i] << " => ";
        int incoming = pg[i];
        int cnt = 0;
        bool flag = true; // true->present
        for (int j = 0; j < fn; j++)
        {
            // empty frame is present
            if (fr[j] == -1)
            {
                q.push(incoming);
                fr[j] = incoming;
                flag = false;
                faults++;
                break;
            }
            else if (fr[j] == incoming)
            {
                // hit
                hits++;
            }
            else
            {
                cnt++;
            }
        }
        // frames is not empty,so replace page with
        //  page which is come 1st
        if (cnt == fn)
        {
            int qfront = q.front();
            q.pop();
            for (int j = 0; j < fn; j++)
            {
                if (fr[j] == qfront)
                {
                    fr[j] = incoming;
                    q.push(incoming);
                    flag = false;
                    faults++;
                    break;
                }
            }
        }
        (flag) ? (cout << "hits :   |") : (cout << "faults : |");
        for (auto page : fr)
        {
            // printing current pages in all frames
            cout << page << " | ";
        }

        cout << endl;
    }
    cout << endl;
    cout << "No. of hits : " << hits << endl;
    cout << "No. of page fault : " << pn - hits << endl;
    cout << "hit ratio  (" << hits << "/" << pn << ") : " << (float)hits / (float)pn << endl;
}
void LRU(int pg[], int pn, int fn)
{
    unordered_set<int> s;
    unordered_map<int, int> indexes;
    int faults = 0;
    for (int i = 0; i < pn; i++)
    {
        bool flag = true; // T->present/hit
        cout << pg[i] << " => ";
        if (s.size() < fn)
        {
            // page is not present in frames
            if (s.find(pg[i]) == s.end())
            {
                s.insert(pg[i]);
                flag = false;
                faults++;
            }
            // storing index of page
            indexes[pg[i]] = i;
        }
        else
        {
            if (s.find(pg[i]) == s.end())
            {
                int index_of_lru = INT_MAX, val;
                for (auto &it : s)
                {
                    if (indexes[it] < index_of_lru)
                    {
                        index_of_lru = indexes[it];
                        val = it;
                    }
                }
                s.erase(val);
                s.insert(pg[i]);
                flag = false;
                faults++;
            }
            indexes[pg[i]] = i;
        }
        (flag) ? (cout << "hits   : |") : (cout << "faults : |") ;
        for (auto it : s)
        {
            cout << it << " |";
        }
        cout << endl;
    }
    int hits = pn - faults;
    cout << "No. of hits : " << hits << endl;
    cout << "No. of Page faults : " << faults << endl;
    cout << "hit ratio (" << (pn - faults) << "/" << pn << ") : " << (float)(hits) / (float)pn << endl;
}
bool search(int key, vector<int> &fr)
{
    for (int i = 0; i < fr.size(); i++)
    {
        if (fr[i] == key)
        {
            return true;
        }
    }
    return false;
}
int predict(int pg[], vector<int> &fr, int pn, int index)
{
    int res = -1, farthest = index;
    for (int i = 0; i < fr.size(); i++)
    {
        int j;
        for (int j = index; j < pn; j++)
        {
            if (fr[i] == pg[j])
            {
                if (j > farthest)
                {
                    farthest = j;
                    res = i;
                }
                break;
            }
            if (j == pn-1)
            {
                // if page is not present
                return i;
            }
        }
    }
    return (res == -1) ? 0 : res;
}

void Optimal(int pg[], int pn, int fn)
{
    vector<int> fr;
    int hits = 0;
    for (int i = 0; i < pn; i++)
    {
        cout << pg[i] << " => ";
        bool flag = false; // T->present/hit
        if (search(pg[i], fr))
        {
            flag = true;
            hits++;
            // continue;
        }

        if (fr.size() < fn && !flag)
        {
            fr.push_back(pg[i]);
        }
        else if(!flag)
        {
            int j = predict(pg, fr, pn, i + 1);
            fr[j] = pg[i];
        }
        (flag) ? (cout << "hits : |") : (cout << "faults:|");
        for (auto it : fr)
        {
            cout << it << " |";
        }
        cout << endl;
    }
    cout << "No. of hits : " << hits << endl;
    cout << "No. of Page fault :" << pn - hits << endl;
    cout << "hit ratio (" << hits << "/" << pn << ") : " << (float)(hits) / (float)pn << endl;

}
int main()
{
    int pg[] = {3, 2, 1, 3, 4, 1, 6, 2, 4, 3, 4, 2, 1, 4, 5, 2, 1, 3, 4};
    int pn = 19; // no. of pages
    int fn = 3;  // frame size
    cout << "================= FIFO ================"<<endl;
    FIFO(pg ,pn , fn);
    cout << "================= LRU ================"<<endl;
    LRU(pg ,pn ,fn);
    cout << "================= Optimal ================" << endl;
    Optimal(pg, pn, fn);
    return 0;
}