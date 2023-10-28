
// =====================================================
// Name : Sarthak Nirgude
// Roll No. : 31155
// Assignment No. : 3
// CRC (Cyclic Redundancy Check)
// =====================================================
#include <bits/stdc++.h>
#define ull unsigned long long
using namespace std;

class CRC
{
    string data, key;
    int ind;
    string codewordS;

public:
    void input(string d, string k)
    {
        this->data = d;
        this->key = k;
    }
    void input_2()
    {
        cout << "Do you want induce error: (y/n)" << endl;
        char chk;
        cin >> chk;
        if (chk == 'Y' || chk == 'y')
        {
            // cout << "Enter the index at which you want to alter bit : " << endl;
            ind = rand();
            ind = ind%8;
        }
        else
        {
            ind = -1;
        }
    }
    int decimalToBinary(int N)
    {
        // To store the binary number
        ull B_Number = 0;
        int cnt = 0;
        while (N != 0)
        {
            int rem = N % 2;
            ull c = pow(10, cnt);
            B_Number += rem * c;
            N /= 2;
            // Count used to store exponent value
            cnt++;
        }
        return B_Number;
    }
    // xor of a & b
    string _xor(string a, string b)
    {
        string ans = "";

        // if bits are same then xor is 0 ,else 1
        for (int i = 1; i < b.length(); i++)
        {
            if (a[i] == b[i])
            {
                ans += "0";
            }
            else
            {
                ans += "1";
            }
        }
        return ans;
    }

    string _mod2Div(string dividend, string divisor)
    {

        // Number of bits to be XORed at a time.
        int pick = divisor.length();

        // Slicing the dividend to appropriate
        // length for particular step
        string tmp = dividend.substr(0, pick);

        int n = dividend.length();

        while (pick < n)
        {
            if (tmp[0] == '1')
            { // Replace the dividend by the result
                // of XOR and pull 1 bit down
                tmp = _xor(divisor, tmp) + dividend[pick];
            }
            else
            {
                tmp = _xor(std::string(pick, '0'), tmp) + dividend[pick];
            }

            pick += 1;
        }

        // For the last n bits, we have to carry it out
        // normally as increased value of pick will cause
        // Index Out of Bounds.
        if (tmp[0] == '1')
            tmp = _xor(divisor, tmp);
        else
            tmp = _xor(std::string(pick, '0'), tmp);

        return tmp;
    }
    void SenderData()
    {
        string appended_data = (data + std::string(key.length() - 1, '0'));
        string remainder = _mod2Div(appended_data, key);
        string codeword = data + remainder;
        codewordS = codeword;
        cout << "Remainder :  " << remainder << endl;
        cout << "Codeword : " << codeword << endl;
    }
    void Receiver()
    {
        string data = codewordS;
        if(ind != -1)
        {
            data[ind] = (data[ind]=='1')?'0':'1';
        }
        string currxor = _mod2Div(data.substr(0, key.size()), key);
        int curr = key.size();
        while (curr != data.size())
        {
            if (currxor.size() != key.size())
            {
                currxor.push_back(data[curr++]);
            }
            else
            {
                currxor = _mod2Div(currxor, key);
            }
        }
        if (currxor.size() == key.size())
        {
            currxor = _mod2Div(currxor, key);
        }
        cerr << "Reductant bits : " << currxor << endl;
        if (currxor.find('1') != string::npos)
        {
            cout << "Error detected " << endl;
            // cerr << currxor << endl;
            cout << "Codeword Discarded" << endl;
            return;
        }
        else
        {
            cout << "Correct data received" << endl;
        }
    }
};

int main()
{
    CRC obj;
    // obj.input("1001", "1011");
    // obj.SenderData();
    // obj.input_2();
    // obj.Receiver();
    string msg = "";
    cout << "\nEnter input : ";
    cin >> msg;
    cout << "Message : " << msg << endl;
    for (int i = 0; i < msg.length(); i++)
    {
        cout << "character : " << msg[i] << endl;
        int c = int(msg[i]);
        cout << "Ascii :" << c << endl;
        int x = obj.decimalToBinary(c);
        cout << "Binary :" << x << endl;
        string data = to_string(x);
        string key = "1011";
        obj.input(data,key);
        obj.SenderData();
        obj.input_2();
        obj.Receiver();
        cout << endl;
    }
    return 0;
}
