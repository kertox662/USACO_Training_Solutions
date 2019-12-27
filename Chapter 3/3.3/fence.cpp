/*
ID: misha2
TASK: fence
LANG: C++                 
*/

#include <iostream>
#include <fstream>
#include <stack>
#include <set>
#include <array>
#include <cmath>
#include <vector>
#include <algorithm>

#define MAX_NODE 501
#define MAX_FENCE 1025

using namespace std;

int graph[MAX_NODE][MAX_NODE];
array<int, MAX_NODE> degree;
stack<int> nodeStack;
int numFence, maxNode = 0;

int main() {
    ofstream fout ("fence.out");
    ifstream fin ("fence.in");

    fin >> numFence;
    for(int i = 0; i < numFence; i++){
        int a, b;
        fin >> a >> b;
        graph[a][b]++;
        graph[b][a]++;
        degree[a]++;
        degree[b]++;
        maxNode = max(maxNode, max(a,b));
    }

    bool foundOdd = false;
    for(int i = 1; i <= maxNode; i++){
        if(degree[i] % 2 == 1){
            nodeStack.push(i);
            foundOdd = true;
            break;
        }
    }
    if(!foundOdd) nodeStack.push(1);

    vector<int> circuit;
    while(!nodeStack.empty()){
        int cur = nodeStack.top();
        bool foundConn = false;
        for(int i = 1; i <= maxNode; i++){
            if(graph[cur][i]){
                graph[cur][i]--;
                graph[i][cur]--;
                nodeStack.push(i);
                foundConn = true;
                break;
            }
        }
        if(!foundConn){
            circuit.push_back(cur);
            nodeStack.pop();
        }
    }

    vector<int> valid(circuit.rbegin(), circuit.rend());
    for(int i : valid) fout << i << endl;


    return 0;
}