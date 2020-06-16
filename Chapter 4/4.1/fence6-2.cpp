/*
ID: misha2
TASK: fence6
LANG: C++                 
*/

#include <iostream>
#include <fstream>
#include <set>
#include <algorithm>
#include <vector>
#include <queue>
#define MAX_FENCES 101
#define INF 1000000

using namespace std;

struct fence{
    int id,length;
};

int N;
fence fences[MAX_FENCES];
int paths[MAX_FENCES][MAX_FENCES];

class comp{
    public:
    bool operator()(pair<int, vector<int> > a, pair<int, vector<int> > b){
        return a.first > b.first;
    }
};

bool idSort(fence a, fence b){
    return a.id < b.id;
}

set<vector<int> > nodes;
priority_queue<pair<int,vector<int> >, vector< pair<int,vector<int> > >, comp> loops;
set<int> visited;
int numNodes;

int shortestLoop(int node){
    loops.push({0,{node}});

    while(!loops.empty()){
        // cout << "\tNODE:" << node << endl;
        pair<int,vector<int> > p = loops.top();
        loops.pop();
        int d = p.first;
        vector<int> path = p.second;
        int curNode = path.back();
        // cout << "Looking:" << curNode << ' ' << d << endl;
        // for(int i : path) cout << i << ' ';
        // cout << endl;
        visited.insert(curNode);
        for(int i = 0; i < numNodes; i++){
            // cout << "HERE1" << endl;
            if(paths[curNode][i] < INF){
                // cout << "HERE2" << endl;
                if(i == node){
                    // cout << "HERE3" << endl;
                    if(path.size() >= 3){
                        // cout << "PATH: ";
                        // for(int i : path){
                        //     cout << i << ' ';
                        // }
                        // cout << endl;
                        // cout << "NODE:" << node << " CUR:" << curNode << " D:" << d << " +" << paths[curNode][i] << endl;
                        return d + paths[curNode][i];
                    }
                    continue;
                }
                if(find(path.begin(), path.end(), i) == path.end()){
                    vector<int> newPath(path.begin(), path.end());
                    newPath.push_back(i);
                    loops.push({d + paths[curNode][i], newPath});
                }
            }
        }
    }
    cout << endl;

    return INF;
}

int main() {
    ofstream fout ("fence6.out");
    ifstream fin ("fence6.in");

    fin >> N;
    for(int i = 1; i <= N; i++){
        int id, l, n1,n2;
        fin >> id >> l >> n1 >> n2;
        fences[i] = {id, l};
        vector<int> leftNode, rightNode;
        leftNode.push_back(id);
        rightNode.push_back(id);
        int c;
        for(int j = 0; j < n1; j++){
            fin >> c;
            leftNode.push_back(c);
        }
        for(int j = 0; j < n2; j++){
            fin >> c;
            rightNode.push_back(c);
        }
        sort( leftNode.begin(),  leftNode.end());
        sort(rightNode.begin(), rightNode.end());
        nodes.insert(leftNode);
        nodes.insert(rightNode);
    }

    sort(fences+1, fences+N+1, idSort);

    // cout << "Number Nodes: " << nodes.size() << endl;
    vector< vector<int> > nodesV;
    int n = 0;
    for(auto v : nodes){
        nodesV.push_back(v);
        // cout << n <<':';
        // for(int i : v){
        //     cout << i << ',';
        // }
        // cout << endl;
        // n++;
    }

    for(int i = 0; i < nodesV.size(); i++){
        paths[i][i] = INF;
        for(int j = i+1; j < nodesV.size();j++){
            int ind1 = 0, ind2 = 0;
            bool found = false;
            while (ind1 < nodesV[i].size() && ind2 < nodesV[j].size()){
                if(nodesV[i][ind1] < nodesV[j][ind2]){
                    ind1++;
                } else if(nodesV[i][ind1] > nodesV[j][ind2]){
                    ind2++;
                } else{
                    found = true;
                    break;
                }
            }

            if(found){
                int segId = nodesV[i][ind1];
                // cout << "Adding Conncetion: ";
                // cout << i << " to " << j << " Length:" << fences[segId].length;
                // cout << ' ' << ind1 << ' ' << ind2 << endl;
                // cout << segId << ' ' << fences[segId].id << ' ' << fences[segId].length << endl;
                paths[i][j] = fences[nodesV[i][ind1]].length;
                paths[j][i] = fences[nodesV[i][ind1]].length;
            }
            else{
                paths[i][j] = INF;
                paths[j][i] = INF;
            }
        }
    }

    numNodes = nodesV.size();
    int minP = INF;
    for(int i = 0; i < numNodes; i++){
        visited.clear();
        while(!loops.empty()) loops.pop();
        int p = shortestLoop(i);
        if(p < minP)
            minP = p;
    }

    fout << minP << endl;
    cout << minP << endl;

    // for(int i = 0; i < nodesV.size(); i++){
    //     cout << "I:" << i << " | ";
    //     for(int j = 0; j < nodesV.size(); j++){
    //         cout << paths[i][j] << ' ';
    //     }
    //     cout << endl;
    // }

    return 0;
}