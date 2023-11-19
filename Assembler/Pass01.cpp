/*
----> Sarthak Nirgude <----
        ◉_◉
----|-----------------|----
*/
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>
#include <regex>
using namespace std;

class SymTabEntry
{
    public:
    int index;
    string symbol;
    int address;

    public:
    SymTabEntry(int index, string symbol, int address)
    {
        this->index = index;
        this->symbol = symbol;
        this->address = address;
    }
};

class LitTabEntry
{
    public:
    int index;
    string literal;
    int address;

    public:
    LitTabEntry(int index, string literal, int address)
    {
        this->index = index;
        this->literal = literal;
        this->address = address;
    }
};

class PoolTabEntry
{
    public:
    int index;
    int address;

    public:
    PoolTabEntry(int index, int address)
    {
        this->index = index;
        this->address = address;
    }
};

class Instruction
{
    public:
    string label;
    string opcode;
    string operand_1;
    string operand_2;

    Instruction()
    {
        this->label = "";
        this->opcode = "";
        this->operand_1 = "";
        this->operand_2 = "";
    }
};


class pass1{
    map<string,string>IS;
    map<string,string>AD;
    map<string,string>DL;
    map<string,string>R;

    vector<SymTabEntry>symTab;
    vector<LitTabEntry>litTab;
    vector<PoolTabEntry>poolTab;
    

    public:

    pass1(){
        IS["STOP"] = "00";
        IS["ADD"] = "01";
        IS["SUB"] = "02";
        IS["MULT"] = "03" ;
        IS["MOVER"] = "04";
        IS["MOVEM"] = "05";
        IS["COMP"] = "06";
        IS["BC"] = "07";
        IS["DIV"] = "08" ;
        IS["READ"] = "09" ;
        IS["PRINT"] = "10";

        AD["START"] = "01";
        AD["END"] = "02";
        AD["ORIGIN"] = "03";
        AD["EQU"] = "04";
        AD["LTORG"] = "05";

        DL["DC"] = "01";
        DL["DS"] = "02" ;

        R["AREG"] = "01";
        R["BREG"] = "02";
        R["CREG"] = "03";
        R["DREG"] = "04";
        R["ANY"] = "06";

        poolTab.push_back(PoolTabEntry(1,1));
    }

    vector<string> Lines(string filename){
        fstream fin;
        fin.open(filename);
        vector<string>temp;
        string line;
        while(!(fin.eof())){
            getline(fin, line);
            temp.push_back(line);
        }

        return temp;
    }
    
    bool checkLabel(string s){
        if(AD[s]!="" || DL[s]!="" || IS[s]!=""){
            return false;
        }return true;
    }

    vector<Instruction> Instruct(vector<string> v){
        vector<Instruction> temp;

        for(int i=0;i<v.size();i++){
            Instruction instr;
            stringstream s(v[i]);
            string word;
            vector<string>words;
            while(s>>word){
                words.push_back(word);
            }

            int j = 0;

            if(checkLabel(words[j])){
                instr.label = words[j];
                j++;
            }

            if(j<words.size()){
                instr.opcode = words[j];
                j++;
            }

            if(j<words.size()){
                instr.operand_1 = words[j];
                j++;
            }

            if(j<words.size()){
                instr.operand_2 = words[j];
                j++;
            }
            temp.push_back(instr);
        }
        return temp;
    }

    void updateSymTab(string label, int lc){

        for(int i=0;i<symTab.size();i++){
            if(symTab[i].symbol == label){
                symTab[i].address = lc;
                return;
            }
        }

        symTab.push_back(SymTabEntry(symTab.size()+1, label, lc));
        
    }

    void updatelitTab(string label){
        int startin = poolTab.back().address-1;
        for(int i=startin; i<litTab.size(); i++){
            if(litTab[i].literal==label){
                return;
            }
        }

        litTab.push_back(LitTabEntry(litTab.size()+1, label, -1));
    }

    int getSymIndex(string s){
        for(int i=0;i<symTab.size();i++){
            if(symTab[i].symbol == s){
                return i;
            }
        }
        return -1;
    }

    int evaluate(string s){
        int ind = find(s.begin(), s.end(), '+')-s.begin();
        if(ind == s.size()){
            ind = find(s.begin(), s.end(), '-')-s.begin();
        }

        if(ind != s.size()){
            int right = stoi(s.substr(ind+1));
            int left = symTab[getSymIndex(s.substr(0,ind))].address;

            if(s[ind]=='+'){
                return left+right;
            }else{
                return left-right;
            }
        }
        else{
            return symTab[getSymIndex(s)].address;
        }
    }

    void processOperand(string s){
        if(s==""){return;}

        if(s[0]=='='){
            updatelitTab(s);
        }
        else if(R[s] == ""){
            if(getSymIndex(s)==-1){
                updateSymTab(s,-1);
            }
        }
    }

    string addOperand(string IC, string operand){
        if(operand == ""){
            return IC;
        }

        if(R[operand] != ""){
            IC += " (" + R[operand] +  ")";
        }else{
            if(operand[0] == '='){
                int ind = -1;
                for(int i=0;i<litTab.size();i++){
                    if(litTab[i].literal == operand){
                        ind = i;
                    }
                }
                IC += "(L " + to_string(ind+1) +  ")";
            }else{
                int ind1 = find(operand.begin(), operand.end(), '+')-operand.begin();
                if(ind1 == operand.size()){
                    ind1 = find(operand.begin(), operand.end(), '-')-operand.begin();
                }
                if(ind1 != operand.size()){
                    string right = operand.substr(ind1);
                    string left = operand.substr(0,ind1);
                    IC += "(S ," + to_string(getSymIndex(left)+1) + ")" + right ;
                }else if(getSymIndex(operand) == -1){
                    IC += "(C " + operand +  ")";
                }else{
                    int ind = getSymIndex(operand);
                    IC += "(S " + to_string(ind+1) +  ")";
                }
            }
        }
        return IC;
    }
    vector<string>process(Instruction instr, int &lc){
        vector<string>temp;
        if(instr.label != ""){
            updateSymTab(instr.label,lc);
        }

        if(AD[instr.opcode] !=""){

            if(instr.opcode == "START"){
                lc = stoi(instr.operand_1);
            }
            else if(instr.opcode == "ORIGIN"){
                int val = evaluate(instr.operand_1);
                lc = val;
            }else if(instr.opcode == "LTORG" || instr.opcode == "END"){
                int startind = poolTab.back().address-1;
                
                for(int i = startind;i<litTab.size();i++){
                    litTab[i].address = lc;
                    string l = litTab[i].literal;
                    string ICLines = to_string(lc) + ".   " + "(DL, 01) (C, "+l.substr(2,l.size()-3)+ ")";
                    temp.push_back(ICLines);
                    lc++;
                }
                poolTab.push_back(PoolTabEntry(poolTab.size()+1, litTab.size()+1));
            }else{
                int val = evaluate(instr.operand_1);
                symTab[getSymIndex(instr.label)].address = val;
            }
    
        }
        else{
            processOperand(instr.operand_1);
            processOperand(instr.operand_2);
        }

        string IC = "";
        if(instr.opcode != "LTORG"){
            if(AD[instr.opcode]!=""){
                IC += "-    (AD , " + AD[instr.opcode] + ")";
            }else if(IS[instr.opcode]!=""){
                IC += to_string(lc) + ". (IS , " + IS[instr.opcode] + ")";
            }else{
                IC += to_string(lc) + ". (DL ," + DL[instr.opcode] +  ")";
            }

            IC = addOperand(IC, instr.operand_1);
            IC = addOperand(IC, instr.operand_2);

            temp.push_back(IC);
        }

        if(IS[instr.opcode] != "" || DL[instr.opcode] != "")
        {
            if(instr.opcode == "DS"){
                int change = stoi(instr.operand_1);
                lc = lc+change;
            }
            else lc++;
        }
        return temp;
    }

    void displayIC(vector<string>v){
        for(int i=0;i<v.size() ; i++){
            cout << v[i] << endl;
        }
    }
    void displayPoolTab()
    {
        cout<<"PoolTab:"<<endl;
        int len = poolTab.size();
        for(int i = 0 ; i < len ; i++)
        {
            cout<<poolTab[i].index<<"  "<<poolTab[i].address<<endl;
        }
    }
    
    void displayLitTab()
    {
        cout<<"Littab"<<endl;
        int len = litTab.size();
        for(int i = 0 ; i < len ; i++)
        {
            cout<<litTab[i].index<<"  "<<litTab[i].literal<<"   "<<litTab[i].address<<endl;
        }
    }
    void displaySymTab()
    {
        cout<<"Symtab : "<<endl;
        int len = symTab.size();
        for(int i = 0 ; i < len ; i++)
        {
            cout<<symTab[i].index<<"  "<<symTab[i].symbol<<"  "<<symTab[i].address<<endl;
        }
    }
    void genrateIC(string filename){
        vector<string>line = Lines(filename);
        vector<Instruction>I = Instruct(line);
        vector<string>IC;
        int len = line.size();
        int lc = 0;

        for(int i=0;i<len;i++){
            vector<string> L = process(I[i], lc);
            for(int j=0;j<L.size();j++){
                IC.push_back(L[j]);
            }
        }

        displayIC(IC);
        displaySymTab();
        displayLitTab();
        displayPoolTab();
    }

};


int main(){
    pass1 p;
    vector<string>line = p.Lines("test_2.txt");
    vector<Instruction>I = p.Instruct(line);
    p.genrateIC("mock01.txt");
}
