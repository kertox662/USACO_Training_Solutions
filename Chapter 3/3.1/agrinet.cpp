/*
ID: misha2
TASK: agrinet
LANG: C++                 
*/

#include <iostream>
#include <fstream>
#include <set>
#include <algorithm>
#define MAX_FARM 150
#define INF 1000000000

using namespace std;

int adj[MAX_FARM][MAX_FARM], mstDist[MAX_FARM];
int N;
set<int> mst;

int main() {
    ofstream fout ("agrinet.out");
    ifstream fin ("agrinet.in");

    fin >> N;
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){fin >> adj[i][j];}
    }

    fill_n(mstDist, MAX_FARM, INF);

    mstDist[0] = 0;
    int treeSize = 0;

    while(mst.size() < N){
        pair<int,int> minNode{-1,INF};
        for(int i = 0; i < N; i++){
            if(mst.find(i) != mst.end()) continue;
            if(mstDist[i] < minNode.second){
                minNode.second = mstDist[i];
                minNode.first = i;
            }
        }
        mst.insert(minNode.first);

        // cout << minNode.first << ' ' << minNode.second << endl;;
        for(int i = 0; i < N; i++){
            mstDist[i] = min(mstDist[i], adj[minNode.first][i]);
        }
        treeSize+=minNode.second;
    }
    fout << treeSize << endl;;

    return 0;
}