/*
ID: misha2
TASK: contact
LANG: C++                 
*/

#include <iostream>
#include <fstream>
#include <string>
#include <bitset>
#include <map>
#include <set>
#include <algorithm>
#include <vector>
#define MAX_DIG 12

using namespace std;

int lower,upper,N;
string code;
map<string, int> freq;


struct lSort{
    bool operator() (const string a, const string b) const{
        if(a.length() < b.length()) return true;
        if(a.length() > b.length()) return false;
        return a < b;
    }
};

map<int, set<string, lSort> >invFreq;

void invMap(){
    for(auto p : freq){
        invFreq[p.second].insert(p.first);
    }
}

int main() {
    ofstream fout ("contact.out");
    ifstream fin ("contact.in");

    fin >> lower >> upper >> N;

    char c;
    while(fin.get(c)){
        if(c == '\n') fin.get(c);
        if(c && c != '\n')
            code += c;
    }
    for(int i = 0; i <= code.length()-lower;i++){
        for(int j = lower; j <= upper && j + i <= code.length(); j++){
            string s = code.substr(i,j);
            freq[s]++;
        }
    }

    set<int, greater<int> > freqs;

    for(auto p : freq){
        freqs.insert(p.second);
    }
    
    invMap();

    int lastPrint = 20000000, nP = 0;
    auto it = freqs.begin();
    for(int i = 0; i < N && i < freqs.size(); i++,it++){
        if(*it <= 0) break;
        fout << *it;

        vector<string> toPrint(invFreq[*it].begin(),invFreq[*it].end());
        cout << "Init:" << toPrint.size() << endl;
        for(int i = toPrint.size()-1; i >= 0; i--){
            if(!(i%6)) toPrint.insert(toPrint.begin()+i, "\n");
            else toPrint.insert(toPrint.begin()+i, " ");
        }
        toPrint.push_back("\n");
        for(string s : toPrint) fout << s;
        
    }
    return 0;
}