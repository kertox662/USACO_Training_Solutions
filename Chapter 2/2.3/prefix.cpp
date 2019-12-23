/*
ID: misha2
TASK: prefix
LANG: C++                 
*/

#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <algorithm>
#include <queue>

using namespace std;

set<string> prims;
string object;
queue<int> nextPos;
set<int> visited;

bool isPrefix(string p, int start){
    if(p.length() > object.length() - start) return false;
    for(int i = 0; i < p.length(); i++){
        if(object[i+ start] != p[i]) return false;
    }
    return true;
}

int main() {
    ofstream fout ("prefix.out");
    ifstream fin ("prefix.in");

    string prim;
    do{
        fin >> prim;
        prims.insert(prim);
    }while (prim != ".");
    prims.erase(".");
    fin >> object;
    string temp;
    while(getline(fin, temp)){
        object += temp;
    }
    object.erase(std::remove(object.begin(), object.end(), '\n'), object.end());
    object.erase(std::remove(object.begin(), object.end(), ' '), object.end());
    
    
    int maxD = 0;
    nextPos.push(0);
    while(!nextPos.empty()){
        int d = nextPos.front();
        maxD = max(d, maxD);
        for(string s : prims){
            if(isPrefix(s, d)){
                if(visited.find(d+s.length()) == visited.end()){
                    nextPos.push(d + s.length());
                    visited.insert(d + s.length());
                }
            }
        }
        nextPos.pop();
    }

    fout << maxD << endl;

    return 0;
}