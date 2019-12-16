/*
ID: misha2
TASK: subset
LANG: C++                 
*/

#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

map<int, vector<pair<int,int> > > pairs;
set<vector<int> > seqs;
int targetSum;
int n;

void makePairs(int m){
    for(int i = 1; i <= m; i++){
        vector<pair<int,int> > v;
        for(int j = 1; 2*j < i; j++){
            v.push_back({j,i-j});
        }
        pairs[i] = v;
    }
}

bool isValid(vector<int> v){
    int s = 0;
    for(int i : v){
        s += i;
        if(count(v.begin(), v.end(), i) > 1) 
            return false;
    }
    if(s != targetSum) return false;
    return true;
}

vector<int> inverse(vector<int> v){
    vector<int> r;
    for(int i = 1; i <= n; i++){
        if(find(v.begin(), v.end(), i) == v.end()) r.push_back(i);
    }
    // for(auto i : r) cout << i << ' ';
    // cout << endl;
    return r;
}

void solve(vector<int> v, int index){
    int d = 0;
    // cout << "Solve: " << index << ' ' << d << " -> ";
    // for(int i : v) cout << i << ' ';
    // cout << endl;
    vector<int> c(v.begin(), v.end());
    sort(c.begin(), c.end());
    if(seqs.find(c) != seqs.end()) return;

    if(isValid(v)){
        auto r = inverse(c);
        seqs.insert(c);
        seqs.insert(r);
    }
    else return;

    if(index >= v.size()) return;

    for(int i = index; i < v.size(); i++, index++){
        for(auto j : pairs[v[i]]){
            vector<int> v2(v.begin(), v.end());
            v2.erase(v2.begin() + index);
            v2.insert(v2.begin() + index, j.second);
            v2.insert(v2.begin() + index, j.first);
            int b;
            if(i == 0) b = 0;
            else b = i-1; 
            solve(v2, b);
        }
        if(i < v.size()-1){
            vector<int> v2(v.begin(), v.end());
            v2[i]++;
            v2[i+1]--;
            if(v2[i] < n && v2[i+1] > 0) solve(v2,i);
        }
    }
}

int main() {
    ofstream fout ("subset.out");
    ifstream fin ("subset.in");

    fin >> n;

    if((n+1)%4 != 0){
        fout << 0 << endl;
        return 0;
    }

    targetSum = ( (n + 1) * n ) / 4;
    // cout << "Target: " << targetSum << endl;

    makePairs(n);
    // for(int i = 1; i <= n; i++){
    //     cout << "I: " << i << ' ';
    //     auto v = pairs[i];
    //     for(auto p : v) cout << '(' << p.first << ',' << p.second << "), ";
    //     cout << endl;
    // }

    vector<int> startingV;
    int tempSum = targetSum;
    for(int i = n; i >= 1 && tempSum > 0; i--){
        if(i <= tempSum){
            startingV.push_back(i);
            tempSum -= i;
        }
    }

    startingV = vector<int>(startingV.rbegin(), startingV.rend());

    // for(int i : startingV) cout << i << ' ';
    // cout << endl;

    solve(startingV, 0);

    // for(auto it = seqs.begin(); it!=seqs.end(); it++){
    //     for(int i : *it) cout << i << ' ';
    //     cout << endl;
    // }

    fout << seqs.size()/2 << endl;

    return 0;
}