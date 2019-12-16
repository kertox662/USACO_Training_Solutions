/*
ID: misha2
TASK: holstein
LANG: C++                 
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <queue>
#include <algorithm>

using namespace std;


vector< vector<int> > feed;
vector<int> vit;
int nV, nF;


bool satisfied(vector<int> vit){
    for(int i = 0; i < vit.size(); i++){
        if(vit[i] > 0) return false;
    }
    return true;
}

vector<int> calcResult(vector<int> seq){
    vector<int> vitC(vit.begin(), vit.end());
    for(int i : seq){
        vector<int> f = feed[i];
        for(int i = 0; i < vitC.size(); i++) vitC[i] -= f[i];
    }

    return vitC;
}

int numActiveBits(int n){
    int i = 0;
    while(n > 0){
        n = n & (n-1);
        i++;
    }
    return i;
}

vector<int> makeSeq(int n){
    vector<int> v;
    for(int i = 0; i < nF; i++){
        if(n & 1<<i) v.push_back(i);
    }
    return v;
}

vector<int> solve(){
    int minBits = nF + 1; 
    vector<int> curSolution;
    for(int i = 1; i < 1 << nF; i++){
        int active = numActiveBits(i);
        if(active < minBits){
            vector<int> seq = makeSeq(i);
            vector<int> r = calcResult(seq);
            if(satisfied(r)){
                curSolution = seq;
                minBits = active;
            }
        }
    }
    return curSolution;
}

int main() {
    ofstream fout ("holstein.out");
    ifstream fin ("holstein.in");

    fin >> nV;


    vit = vector<int>(nV);
    for(int i = 0; i < nV; i++) fin >> vit[i];

    fin >> nF;
    for(int i = 0; i < nF; i++){
        feed.push_back(vector<int>(nV));
        for(int j = 0; j < nV; j++) fin >> feed[i][j];
    }

    vector<int> v = solve();
    fout << v.size();
    for(int i : v) fout << ' ' << i + 1;
    fout << endl;

    return 0;
}