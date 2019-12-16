/*
ID: misha2
TASK: milk3
LANG: C++                 
*/

#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <vector>
#include <array>

using namespace std;

/*STRATEGY:
Depth First Search
Simulate all possible states and actions recursively
Output all of the values that bucket C was at any point
*/

string getID(array<array<int, 2> ,3> state){
    string id = "";
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 2; j++){
            id += state[i][j];
            if(i != 2 && j != 1) id += ':';
        }
    }
    return id;
}

void markVisit(array<array<int, 2> ,3> state, set<string> *visited){
    string id = getID(state);
    visited->insert(id);
}

void solve(array<array<int, 2> ,3> state, set<string> *visited, set<int> *result){
    string id = getID(state);
    if(visited->find(id) != visited->end()) return;
    markVisit(state, visited);

    for(int i = 0; i < 3; i++){
        for(int j = 1; j <= 2; j++){
            array<array<int, 2> ,3> temp = state;
            int giveMilk = temp[i][1];
            int curMilk = temp[(i+j)%3][1];
            temp[(i+j)%3][1] = min(curMilk + giveMilk, temp[(i+j)%3][0]);
            temp[i][1] -= temp[(i+j)%3][1] - curMilk;
            if(temp[0][1] == 0){
                result->insert(temp[2][1]);
            }
            solve(temp, visited, result);
        }
    }
}

int main() {
    ofstream fout ("milk3.out");
    ifstream fin ("milk3.in");

    int a,b,c;
    fin >> a >> b >> c;

    array<array<int, 2> ,3> state = { { {a,0},
                                        {b,0},
                                        {c,c}
                                    } };
    array<array<int, 2> ,3> t = state;

    set<int> result;
    set<string> visited;

    result.insert(c);
    result.insert(max(c - b, 0));

    solve(state, &visited, &result);

    vector<int> out(result.begin(), result.end());

    for(int i = 0; i < out.size(); i++){
        fout << out[i];
        if(i < out.size() - 1) fout << ' ';
    }
    fout << endl;

    return 0;
}