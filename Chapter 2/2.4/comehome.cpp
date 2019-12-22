/*
ID: misha2
TASK: comehome
LANG: C++                 
*/

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <cmath>
#include <set>
#define MAX_SIZE 52
#define BARN 51
#define MAX_DIST 1000000000

using namespace std;

string code = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

int adj[MAX_SIZE][MAX_SIZE] {};
set<int> available, start;

int main() {
    ofstream fout ("comehome.out");
    ifstream fin ("comehome.in");

    int n;
    fin >> n;
    for(int i = 0; i < n; i++){
        char a,b;
        int d;
        fin >> a >> b >> d;
        if(a == b) continue;
        int x = code.find(a), y = code.find(b);
        if(adj[x][y] == 0){
            adj[x][y] = d;
            adj[y][x] = d;
        }else{
            adj[x][y] = min(adj[x][y], d);
            adj[y][x] = adj[x][y];
        }
        if(x < 26 || x == 51) available.insert(x);
        else start.insert(x);
        if(y < 26 || y == 51) available.insert(y);
        else start.insert(y);
    }

    pair<int, int> minDist{MAX_DIST,-1};

    for(int i : start){
        set<pair<int,int> > toVisit;
        set<int> visited;
        toVisit.insert({0,i});
        while(toVisit.size() > 0){
            pair<int,int> field = *toVisit.begin();
            if(visited.find(field.second) != visited.end()){
                toVisit.erase(toVisit.begin());
                continue;
            }
            visited.insert(field.second);

            if(field.second == BARN){
                if(field.first < minDist.first){
                    minDist = {field.first, i};
                }
                break;
            }

            for(int to : available){
                if(adj[to][field.second] > 0){
                    toVisit.insert({field.first + adj[to][field.second], to});
                }
            }

            toVisit.erase(toVisit.begin());
        }
    }

    fout << code[minDist.second] << ' ' << minDist.first << endl;

    return 0;
}