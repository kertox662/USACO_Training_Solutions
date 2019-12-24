/*
ID: misha2
TASK: butter
LANG: C++                 
*/

#include <iostream>
#include <fstream>
#include <map>
#include <set>
#include <vector>
#include <queue>
#define MAX_PAST 801
#define MAX_COW 500
#define INF 10000000

using namespace std;

long long past[MAX_PAST][MAX_PAST], nPast, nPath;
int cows[MAX_COW], nCow;
map<int, vector<int> > conns;
map<int, vector<int> > cowLoc;
set<int> starts;

int main() {
    ofstream fout ("butter.out");
    ifstream fin ("butter.in");

    fin >> nCow >> nPast >> nPath;
    for(int i = 0; i < nCow; i++){
        fin >> cows[i];
        cowLoc[cows[i]].push_back(i);
    }
    for(int i = 1; i <= nPast; i++){
        for(int j = 1; j<= nPast;j++){
            if(i == j) past[i][i] = 0;
            else past[i][j] = INF;
        }
    }

    for(int i = 0; i < nPath; i++){
        int a,b, cost;
        fin >> a >> b >> cost;
        past[a][b] = cost;
        past[b][a] = cost;
        conns[a].push_back(b);
        conns[b].push_back(a);
    }

    int nT = 0;

    for(int c = 0; c <= nCow; c++){
        int nodeToDo = cows[c];
        if(starts.find(nodeToDo) != starts.end()) continue;
        
        int i = nodeToDo;
        set<int> visited;
        priority_queue<pair<int,int>, vector<pair<int,int> >, greater<pair<int,int> > > q;

        for(int cow = 1; cow <= nPast; cow++){
            if(cow == i) continue;
            if(past[i][cow] != INF) q.push({past[i][cow], cow});
        }
        visited.insert(nodeToDo);

        int n = 0;

        while(q.size() && visited.size() < nPast){
            pair<long long,int> p = q.top();
            n++;
            q.pop();
            int dist = p.first, node = p.second;
            if(visited.find(node) != visited.end()) continue;
            visited.insert(node);
            past[i][node] = dist;
            for(int next : conns[node]){
                if(visited.find(next) == visited.end())
                    q.push({dist+past[node][next], next});
            }
            // for(int next = 1; next <= nPast; next++){
            //     if(next == node || next == i) continue;
            //     if(past[node][next] != INF)
            //     if(visited.find(next) == visited.end()){
            //         q.push({dist+past[node][next], next});
            //     }
            // }
        }
        // cout << "I:" << i << ' ' << n << endl;
        // cout << q.size() << ' ' << visited.size() << endl;
        nT += n;

    }
    cout << "NT:" << nT << endl;
    // for(int i = 1; i <= nPast; i++){
    //     for(int j = 1; j <= nPast; j++){
    //         cout << past[i][j] << ' ';
    //     }
    //     cout << endl;
    // }

    int minDist = (1 << 30);
    for(int i = 1; i <= nPast; i++){
        int curDist = 0;
        for(int c = 0; c < nCow; c++){
            curDist += past[i][cows[c]];
        }
        if(curDist < minDist) minDist = curDist;
    }

    //OUT//
    cout << minDist << endl;
    fout << minDist << endl;

    return 0;
}