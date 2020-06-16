/*
ID: misha2
TASK: fence6
LANG: C++                 
*/

#include <iostream>
#include <fstream>
#include <set>
#include <queue>
#define MAX_FENCES 101
#define INF 1000000

using namespace std;

struct fence{
    int id,length;
    set<int> conns;
};

int N;
fence fences[MAX_FENCES];

set<int> visited;
priority_queue<pair<int, int> > paths;

// int shortestLoop(fence *f){
//     int target = f->id;
//     paths.push({0,target});

//     while(!paths.empty()){
//         pair<int,int> p = paths.top();
//         paths.pop();
//         int d = p.first, id = p.second;
//         fence *curF = &fences[id];
//         d += curF->length;
//         visited.insert(id);
//         for(int c : curF->conns){
//             if(c == target){
//                 if(d > f->length + curF->length){
//                     cout << "T:" << target << " LAST:" << id << " D:" << d << endl;
//                     for(int i : visited){
//                         cout << i << ',';
//                     }
//                     cout << endl;
//                     return d;
//                 }
//                 break;
//             }
//             if(visited.find(c) == visited.end()){
//                 paths.push({d, c});
//             }
//         }
//     }
//     return INF;
// }

int main() {
    ofstream fout ("fence6.out");
    ifstream fin ("fence6.in");

    fin >> N;
    for(int i = 1; i <= N; i++){
        int id, l, n1,n2;
        fin >> id >> l >> n1 >> n2;
        fences[i] = {id, l};

        set<int> conns;
        for(int j = 0; j < n1+n2; j++){
            int c;
            fin >> c;
            conns.insert(c);
        }
        fences[i].conns = conns;
    }

    int minP = INF;
    for(int i = 1; i <= N; i++){
        visited.clear();
        
        while(!paths.empty())
            paths.pop();

        int p = shortestLoop(&fences[i]);
        if(p < minP)
            minP = p;
    }

    fout << minP << endl;
    cout << minP << endl;

    return 0;
}