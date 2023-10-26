#include<bits/stdc++.h>
using namespace std;

int main(){

    ifstream fin,kin,mdtin,mntin;
    fin.open("output.txt");
    kin.open("KPDTAB.txt");
    mdtin.open("MDT.txt");
    mntin.open("MNT.txt");

    ofstream fout;
    fout.open("machine_code.txt");

    string line,word;

    // Data structures for storing table values
    
    // For KPDT
    vector<pair<string,string>> kpdt(1); // column - <parameter> <def. value>
    while(getline(kin,line)){
        stringstream ss(line);
        ss >> word;

        pair<string,string> pr = {"",""};
        pr.first = word;
        ss >> word;
        pr.second = word;
        kpdt.push_back(pr);
    }

    cout << "\n" << "KPDT" << "\n";
    for(int i = 0;i < kpdt.size();i++) cout << kpdt[i].first << " " << kpdt[i].second << "\n";

    // For MDT
    vector<vector<string>> mdt(1); // Will store all the instructions and the coresponding parameter index
    while(getline(mdtin,line)){
        stringstream ss(line); // MOVER (P,3), ='5'
        ss >> word;

        vector<string> a;
        a.push_back(word); 

        while(ss >> word){
            if(word[word.size()-1] == ',')
                word = word.substr(0,word.size()-1);

            if(word[0] == '('){ 
                int commaInd = word.size();
                for(int i = 0;i < word.size();i++){ 
                    if(word[i] == ','){
                        commaInd = i;
                        break;
                    }
                }
                word = word.substr(commaInd+1); 
                word = word.substr(0,word.size()-1);
            }           
            a.push_back(word);
        }
        mdt.push_back(a);
    }

    cout << "\n" << "MDT" << "\n";
    for(int i = 0;i < mdt.size();i++) {for(int j = 0;j < mdt[i].size();j++) cout << mdt[i][j] << " "; cout << "\n";}

    // MNT Table
    vector<array<int,4>> mnt(1); 
    map<string,int> mntMap; 
    while(getline(mntin,line)){  
        stringstream ss(line);
        ss >> word;
        mntMap[word] = mnt.size();
        cout << word << "\n";

        array<int,4> a;
        for(int i = 0;i < 4;i++){
            if(ss >> word){
                a[i] = stoi(word);
            }
        }
        mnt.push_back(a);
    }

    cout << "\n" << "MNT" << "\n";
    for(int i = 0;i < mnt.size();i++) {for(int j = 0;j < 4;j++) cout << mnt[i][j] << " "; cout << "\n";} 

    // Processing the calls
    while(getline(fin,line)){ // INCR_M MEM_VAL=A, INCR_VAL=B, REG=AREG 
        stringstream ss(line);
        ss >> word;
        
        int mntInd = mntMap[word];
        int totalPara = mnt[mntInd][0] + mnt[mntInd][1];
        vector<string> aptab(totalPara + 1);
        map<string,int> kpInd;
        
        int indInAp = mnt[mntInd][0] + 1; // PP + KP
        for(int i = 0;i < mnt[mntInd][1];i++){
            int indInKpd = mnt[mntInd][3] + i;
            aptab[indInAp] = kpdt[indInKpd].second;
            kpInd[kpdt[indInKpd].first] = indInAp;
            indInAp++; 
        }
        
        int ppInd = 1;
        while(ss >> word){ 
            if(word[0] == '&')
                word = word.substr(1);
            if(word[word.size()-1] == ',')
                word = word.substr(0,word.size()-1);

            int equalInd = -1;
            for(int i = 0;i < word.size();i++){
                if(word[i] == '='){
                    equalInd = i;
                    break;
                }
            }    

            if(equalInd != -1){
                string para = word.substr(0,equalInd);
                string val = word.substr(equalInd+1);
                aptab[kpInd[para]] = val;
            }
            else{
                aptab[ppInd] = word;
                ppInd++; 
            }
        }

        for(int i = mnt[mntInd][2];true;i++){
            if(mdt[i][0] == "MEND"){
                break;
            }
            fout << "+ " << mdt[i][0] << " ";

            for(int j = 1;j < mdt[i].size();j++){
                if(mdt[i][j][0] == '='){
                    fout << mdt[i][j]; 
                }
                else{
                    int ind = stoi(mdt[i][j]);
                    fout << aptab[ind];
                }

                if(j != mdt[i].size() - 1)
                    fout << ", ";
            }
            fout << "\n";
        }
        
    }
    
    return 0;
}