/*
ID: misha2
TASK: concom
LANG: C++                 
*/

#include <iostream>
#include <fstream>
#include <set>
#include <queue>
#define MAX_COMP 100

using namespace std;

set<int> owned;
int owners[MAX_COMP+1] = {0}, N;
int own[MAX_COMP+1][MAX_COMP+1] = {{0}};
queue<int> toCheck;


int main() {
    ofstream fout ("concom.out");
    ifstream fin ("concom.in");

    fin >> N;
    for (int i = 0; i < N; i++){
        int a,b,c;
        fin >> a >> b >> c;
        own[a][b] = c;
    }

    for(int i = 1; i <= MAX_COMP; i++){
        if(owned.find(i) != owned.end()) continue;

        toCheck.push(i);
        while(!toCheck.empty()){
            int cur = toCheck.front();
            toCheck.pop();

            for(int c = 1; c <= MAX_COMP; c++){
                if(owned.find(c) != owned.end()) continue;
                if(c == cur || c == owners[cur]) continue;
                if(own[cur][c] > 50){ //If directly owned by a different company
                    owners[c] = cur;
                    owned.insert(c);
                    toCheck.push(c);
                    int temp = cur;
                    
                    set<int> visited;
                    while (temp != 0 && owners[owners[temp]] != temp){
                        int owner = owners[temp];
                        if(visited.find(owner) != visited.end()) break;
                        visited.insert(owner);
                        own[owner][c] += own[cur][c];
                        temp = owner;
                    }
                }
                else{ //If not directly own by a different company, cascade up
                    int temp = cur;
                    set<int> visited;
                    while (owners[temp] != 0 && owners[owners[temp]] != temp){
                        int owner = owners[temp];
                        if(visited.find(owner) != visited.end()) break;
                        visited.insert(owner);
                        own[owner][c] += own[cur][c];
                        if(own[owner][c] > 50){
                            if(owned.find(c) == owned.end()){
                                owned.insert(c);
                                toCheck.push(c);
                                owners[c] = owner;
                            }
                        }
                        temp = owner;
                    }
                }
            }
        }
    }

    for(int i = 1; i <= MAX_COMP; i++){
        set<int> control = {i};
        for(int n = 1; n <= MAX_COMP; n++){
            if(own[i][n] > 50 && i != n) control.insert(n);
        }
        for(int j = 1; j <= MAX_COMP; j++){
            bool valid = false;
            for(int k : control) 
                if (own[k][j] > 50 && k != j){
                    valid = true;
                    break;
                }
            if(valid && i != j){
                fout << i << ' ' << j << endl;
            }
        }
    }
    return 0;
}