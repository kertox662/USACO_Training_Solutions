/*
ID: misha2
TASK: cowtour
LANG: C++                 
*/

#include <iostream>
#include <fstream>
#include <iomanip>
#include <set>
#include <vector>
#include <cmath>
#include <algorithm>
#define MAX_FIELD 150
#define INF 1000000000

using namespace std;

double adj[MAX_FIELD][MAX_FIELD];
int N;
pair<int,int> coor[MAX_FIELD];
set<int> visited;
set<int> fields[MAX_FIELD];
vector<pair<set<int>, pair<int,int> > > pastures;

double dist(pair<int,int> a, pair<int,int> b){
    return sqrt((a.first - b.first) * (a.first-b.first) + (a.second - b.second) * (a.second - b.second));
}

int main() {
    ofstream fout ("cowtour.out");
    ifstream fin ("cowtour.in");

    fin >> N;
    for(int i = 0; i < N; i++){
        int x,y;
        fin >> x >> y;
        coor[i] = {x,y};
    }

    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            char c;
            fin.get(c);
            if(c == '\n')fin.get(c);
            if(c == '1'){
                adj[i][j] = dist(coor[i], coor[j]);
            }else adj[i][j] = INF;
        }
    }

    for(int k = 0; k < N; k++){
        for(int i = 0; i < N; i++){
            for(int j = 0; j < N; j++){
                if(i == j) continue;
                adj[i][j] = min(adj[i][j], adj[i][k] + adj[k][j]);
            }
        }
    }

    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            if(adj[i][j] == INF) adj[i][j] = 0;
        }
    }

    set<int> visited;
    for(int i = 0; i < N; i++){
        if(visited.find(i) != visited.end()) continue;
        visited.insert(i);
        set<int> pasture = {i};
        for(int j = i+1; j < N; j++){
            if(adj[i][j] != 0){
                visited.insert(j);
                pasture.insert(j);
            }
        }
        int mD = 0;
        pair<int,int> maxPair;
        for(int n : pasture){
            for(int m : pasture){
                if (adj[n][m] > mD){
                    mD = adj[n][m];
                    maxPair = {n,m};
                }
            }
        }
        pastures.push_back({pasture, maxPair});
    }

    double minDiam = INF;
    for(int i = 0; i < pastures.size(); i++){
        for(int j = i+1; j < pastures.size(); j++){
            set<int> one = pastures[i].first, two = pastures[j].first;
            pair<int,int> maxA = pastures[i].second, maxB = pastures[i].second;
            double diamM1 = adj[maxA.first][maxA.second], diamM2 = adj[maxB.first][maxB.second], diamM = max(diamM1, diamM2);
            for(int a : one){
                for(int b : two){
                    double diamA = *max_element(adj[a], adj[a]+N);
                    double diamB = *max_element(adj[b], adj[b]+N);
                    double d = dist(coor[a], coor[b]);
                    double diam = diamA + diamB + d;
                    diam = max(diam, diamM);
                    minDiam = min(minDiam, diam);
                    // cout << a <<',' << b << ':' <<minDiam << endl;
                }
            }
        }
    }

    fout << fixed << setprecision(6);
    fout << minDiam << endl;

    // cout << "NUMP:" << pastures.size() << endl;
    // for(set<int> s : pastures) {
    //     for(int i : s) cout << i << ' ';
    //     cout << endl;
    // }

    // cout << setprecision(12) << endl;

    // for(int i = 0; i < N; i++){
    //     for(int j = 0; j < N; j++){
    //         // cout << ((adj[i][j])?"T ":"F ");
    //         cout << j <<':'<<adj[i][j] << ' ';
    //     }
    //     cout << endl;
    // }

    return 0;
}