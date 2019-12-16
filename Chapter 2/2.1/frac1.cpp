/*
ID: misha2
TASK: frac1
LANG: C++                 
*/

#include <iostream>
#include <fstream>
#include <set>
#include <vector>
#include <algorithm>

using namespace std;

int gcd(int a, int b){
    int r = a%b;
    if(r == 0) return b;
    else return gcd(b,r);
}

bool compareFrac(pair<int,int> a, pair<int,int> b){
    return (a.first*b.second < b.first*a.second)?true:false;
}


pair<int,int> reduce(pair<int,int> p){
    if (p.first == 0) return {0,1};
    int f = gcd(p.second, p.first);
    
    return {p.first/f, p.second/f};
}

set<pair<int,int> > fracs;

int main() {
    ofstream fout ("frac1.out");
    ifstream fin ("frac1.in");

    int N;
    fin >> N;

    for(int i = 1; i <= N; i++){
        for(int j = 0; j <= i; j++){
            pair<int,int> f = {j,i};
            f = reduce(f);
            fracs.insert(f);
        }
    }

    vector<pair<int,int> > fracsV(fracs.begin(), fracs.end());

    sort(fracsV.begin(), fracsV.end(), compareFrac);


    for(auto f : fracsV) fout << f.first << "/" << f.second << endl;
    return 0;
}