/*
ID: misha2
TASK: lamps
LANG: C++                 
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <set>

using namespace std;
int N, C;
vector<int> on, off;
set<vector<bool> > valid;

int numActiveBits(int x){
    int s = 0;
    while(x > 0){
        x = x & (x-1);
        s++;
    }
    return s;
}

bool checkValidClicks(int c){
    int b = numActiveBits(c);
    if(b > C) return false;
    return (b%2 == C%2);
}

bool checkValidLamps(bool lamps[]){
    for(int i : on) if(lamps[i] == false) return false;
    for(int i : off) if(lamps[i] == true) return false;
    return true;
}

void toggle(bool lamps[]){
    for(int i = 0; i <= N; i++) lamps[i] = (!lamps[i]);
}

void toggleAlternate(bool lamps[], int start){
    for(int i = start; i<=N; i+=2) lamps[i] = (!lamps[i]);
}

void toggle3K(bool lamps[]){
    for(int i = 1; i <= N; i+=3) lamps[i] = (!lamps[i]);
}

void applyStates(bool lamps[], int states){
    if(states&1) toggle(lamps);
    if(states&2) toggleAlternate(lamps, 1);
    if(states&4) toggleAlternate(lamps,2);
    if(states&8) toggle3K(lamps);
}

int main() {
    ofstream fout ("lamps.out");
    ifstream fin ("lamps.in");

    fin >> N >> C;
    int state;
    fin >> state;

    // cout << N << ' ' << C << endl;
    
    while(state != -1){
        on.push_back(state);
        fin >> state;
    }

    fin >> state;
    while(state != -1){
        off.push_back(state);
        fin >> state;
    }

    for(int i = 0; i < 16; i++){
        bool lamps[N+1];
        for(int j = 0; j <= N; j++) lamps[j] = true;
        if(!checkValidClicks(i)) continue;
        else{
            applyStates(lamps, i);
            if(checkValidLamps(lamps)){
                vector<bool> l(lamps+1, lamps + N + 1);
                valid.insert(l);
                // for(bool b : l) cout << b;
                // cout << endl;
            }
        }
    }

    for(auto l : valid){
        for(bool b : l) fout << b;
        fout << endl;
    }

    if(valid.size() == 0) fout << "IMPOSSIBLE" << endl;

    return 0;
}