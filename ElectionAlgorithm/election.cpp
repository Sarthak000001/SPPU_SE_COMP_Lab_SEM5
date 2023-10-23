#include <bits/stdc++.h>
#include <unistd.h>
using namespace std;

class Node
{
public:
    int id;

    Node()
    {
        id = 0;
    }

    Node(int i)
    {
        id = i;
    }
};

class Ring
{
public:
    int num;
    vector<Node> vec;
    Ring()
    {
        num = 0;
        cout << "----------------------------\n";
        cout << "Enter number of Nodes : ";
        cin >> num;
        cout << "\n----------------------------\n";
        for (int i = 0; i < num; i++)
        {
            Node obj;
            cout << "Enter ID of " << i + 1 << " Node : ";
            cin >> obj.id;
            vec.push_back(obj);
        }
    }
    void detect()
    {
        sort(vec.begin(), vec.end(), [](const Node &l, const Node &r)
             { return l.id < r.id; });
        sleep(2);
        cout << "--------------------------\n";
        cout << "Co-ordinator " << vec.back().id << " failed !\n";
        cout << "--------------------------\n\n";
        vec.pop_back();
        num--;
    }
    void elect()
    {
        cout << "\nconsider " << vec.back().id << " is new Co-ordinator\n\n";
        cout << "\tMessage Passing";
        cout << "\n________________________________\n\n";
        sleep(2);
        int i = 0;
        int index = num - 1;
        while (i < num)
        {
            cout << "Message passed from " << vec[index].id << " to " << vec[(index + 1) % (num)].id << endl;
            sleep(2);
            i++;
            index = (index + 1) % num;
        }
        cout << "________________________________\n\n";
        cout << "New elected Co-ordinator is : " << vec.back().id << " !";
    }
};

class Bully
{
public:
    int num;
    vector<Node> vec;
    Bully()
    {
        num = 0;
        cout << "\n----------------------------\n";
        cout << "Enter number of Nodes : ";
        cin >> num;
        cout << "\n----------------------------\n";
        for (int i = 0; i < num; i++)
        {
            Node obj;
            cout << "Enter ID of " << i + 1 << " Node : ";
            cin >> obj.id;
            vec.push_back(obj);
        }
    }
    void detect()
    {
        sort(vec.begin(), vec.end(), [](const Node &l, const Node &r)
             { return l.id < r.id; });
        cout << "--------------------------";
        cout << "\nCurrent Co-ordinator is : " << vec.back().id << endl;
        sleep(1);
        cout << "--------------------------\n";
        cout << "Co-ordinator " << vec.back().id << " failed !\n";
        cout << "--------------------------\n\n";
        vec.pop_back();
        num--;
    }
    void elect()
    {
        int newCo = rand() % (num);
        cout << "Detected by : " << newCo << endl;
        sleep(1);
        cout << "Election Initialize\n";
        sleep(1);
        cout << "________________________________\n\n";
        while (newCo != num + 1)
        {
            int j = newCo;
            for (int i = newCo; i <= num; i++)
            {
                if (j > num + 1)
                    break;
                sleep(1);
                cout << "Message sent from " << newCo << " to " << ++j << endl;
            }
            for (int i = num; i > newCo; i--)
            {
                sleep(1);
                cout << "ACK sent from " << i << " to " << newCo << endl;
            }
            newCo++;
            cout << "________________________________\n\n";
        }
        cout << "New elected Co-ordinator is : " << vec.back().id << " !";
    }
};

int main()
{

    while (true)
    {
        cout << "\n================ MENU ================n\n";
        int choice;
        cout << "\n\t1. Ring Algorithm\n\t2. Bully Algorithm\n";
        cout << "\nEnter choice : ";
        cin >> choice;

        if (choice == 1)
        {
            Ring r;
            r.detect();
            r.elect();
        }
        else if (choice == 2)
        {
            Bully b;
            b.detect();
            b.elect();
        }
        else
        {
            exit(0);
        }
    }
    return 0;
}
